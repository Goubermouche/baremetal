#pragma once
#include "utility/containers/dynamic_array.h"
#include "utility/system/filepath.h"

namespace utility {
	struct directory {
#ifdef SYSTEM_WINDOWS
		static auto collect_files(const filepath& root_path) -> dynamic_array<filepath> {
			if(!root_path.is_directory()) {
				return {}; // root_path is not a directory
			}

			dynamic_array<filepath> result;
			dynamic_array<dynamic_string_w> folders;
			const dynamic_string_w root_w = string_to_string_w(root_path.get_string());

			folders.push_back(string_to_string_w(root_path.get_string()));

			while(!folders.is_empty()) {
				const dynamic_string_w current = folders.pop_back();

				wchar_t temp_path[2048] = {0};
				WIN32_FIND_DATAW fdFile;
				HANDLE hFind;

				i32 written = swprintf(temp_path, 2048, L"%s/*.*", current.get_data());
				ASSERT(written > 0, "invalid path detected");

				if((hFind = FindFirstFileW(temp_path, &fdFile)) == INVALID_HANDLE_VALUE) {
					ASSERT(false, "Path '{}' not found", current);
					return {};
				}

				do {
					// find first file will always return "." and ".." as the first two directories.
					if(wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0) {
						written = swprintf(temp_path, 2048, L"%s/%s", current.get_data(), fdFile.cFileName);
						ASSERT(written > 0, "invalid path detected");

						if(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
							// folder
							dynamic_string_w child_directory = temp_path;
							folders.push_back(child_directory);
						}
						else {
							// file
							dynamic_string_w file_path_w = temp_path;
							dynamic_string_w relative_path_w = file_path_w.substring(root_w.get_size() + 1); // Get path relative to root
							result.push_back(string_w_to_string(relative_path_w));
						}
					}
				} while(FindNextFileW(hFind, &fdFile)); // find the next file

				FindClose(hFind);
			}

			return result;
		}

		static auto exists(const filepath& path) -> bool {
			const DWORD attr = GetFileAttributesA(path.get_data());

			if(attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY)) {
				return true; // folder exists
			}

			return false; // folder does not exist or is not accessible
		}

		static void create_if_not_exists(const filepath& path) {
			if(exists(path)) {
				return;
			}

			if(!CreateDirectoryA(path.get_data(), nullptr)) {
				ASSERT(false, "failed to create directory");
			}
		}

		static void remove(const filepath& path) {
			if(!RemoveDirectory(string_to_string_w(path.get_string()).get_data())) {
				ASSERT(false, "failed to delete directory '{}'", path);
			}
		}	
#endif
		static auto read(const filepath& path) -> dynamic_array<filepath> {
			dynamic_array<filepath> result;
			DIR* dir = opendir(path.get_data());
			struct dirent* entry;
			
			ASSERT(dir, "failed to open directory '{}'\n", path);


			while((entry = readdir(dir)) != nullptr) {
				if(compare_strings(entry->d_name, ".") != 0 && compare_strings(entry->d_name, "..") != 0) {
					result.push_back(path / entry->d_name);
				}
			}

			closedir(dir);
			return result;
		}

		static auto exists(const filepath& path) -> bool {
			DIR* dir = opendir(path.get_data());

			if(dir) {
				closedir(dir);
				return true;
			} else {
				return false;
			}
		}
	};

	struct file {
#ifdef SYSTEM_WINDOWS
		static auto exists(const filepath& path) -> bool {
			const DWORD attr = GetFileAttributesA(path.get_data());

			if(attr != INVALID_FILE_ATTRIBUTES) {
				return true;
			}

			return false;
		}
#endif
		static auto get_file_line_count(const filepath& path) -> u64 {
			FILE *file = fopen(path.get_data(), "rb");
			ASSERT(file, "failed to open file '{}'\n", path);

			u64 line_count = 0;
			char ch;

			while((ch = fgetc(file)) != EOF) {
				if(ch == '\n') {
					++line_count;
				}
			}

			if(line_count == 0 && ch != EOF) {
				++line_count;
			}

			fclose(file);

			return line_count;
		}

		template<typename type>
		static void write(const filepath& path, const type& value) {
			FILE *file = fopen(path.get_data(), "wb");
			ASSERT(file, "failed to open file '{}'\n", path);
			const size_t size = value.get_size();
			fwrite(value.get_data(), sizeof(typename type::element_type), size, file);
			fclose(file);
		}

		static auto read(const filepath& path) -> dynamic_string {
			FILE* file = fopen(path.get_data(), "rb");
			dynamic_string result;

			ASSERT(file, "failed to open file '{}'\n", path);

			fseek(file, 0, SEEK_END);
			u32 file_size = ftell(file);
			fseek(file, 0, SEEK_SET);

			result.resize(file_size);

			char* write_ptr = result.get_data();
			constexpr u64 chunk_size = 128'000;
			char buffer[chunk_size];

			while(true) {
				u64 bytes_read = fread(buffer, 1, chunk_size, file);

				if(bytes_read > 0) {
					memcpy(write_ptr, buffer, bytes_read);
					write_ptr += bytes_read;
				}

				if(bytes_read < chunk_size) {
					if(feof(file)) {
						break;
					}

					if(ferror(file)) {
						fclose(file);
						ASSERT(false, "unhandled error while reading file '{}\n'", path);
					}
				}
			}

			fclose(file);

			return result;
		}
#ifdef WINDOWS_SYSTEM
		static void write(const filepath& path, const dynamic_string& data) {
			// ensure parent directory exists
			directory::create_if_not_exists(path.get_parent_path());

			// open file for writing
			FILE* file;
			if(fopen_s(&file, path.get_data(), "w")) {
				// ASSERT(false, "failed to open file '{}'", path.get_data());
			}

			if(file == nullptr) {
				// ASSERT(false, "failed to write to file '{}'", path);
			}

			// write data to file
			if(fwrite(data.get_data(), sizeof(dynamic_string::element_type), data.get_size(), file) != data.get_size()) {
				ASSERT(false, "failed to write to file '{}'", path);

				if(fclose(file)) {
					// ASSERT(false, "failed to close file '{}'", path);
				}

				return;
			}

			// close file
			if(fclose(file)) {
				// ASSERT(false, "failed to close file '{}'", path);
			}
		}
#endif
	};
} // utility
