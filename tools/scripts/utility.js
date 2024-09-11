const fs = require("fs");
const path = require("path");
const { execSync } = require('child_process');

function calculate_layout(data) {
  let layout = [];

  data.forEach(row => {
    while(layout.length < row.length) {
      layout.push(0);
    }

    row.forEach((element, column_i) => {
      layout[column_i] = Math.max(layout[column_i], element.length);
    });
  });

  return layout;
}

function apply_layout(layout, data, line_prefix, line_postfix) {
  let result = "";
  let layout_width = 0;

  layout.forEach(l => {
    layout_width += l + 2;
  });

  layout_width -= 2;

  data.forEach(row => {
    result += line_prefix;
    let row_arr = [];

    row.forEach((element, column_i) => {
      row_arr.push(element.padEnd(layout[column_i], ' '));

      if(column_i + 1 !== row.length) {}
      else {
        result += row_arr.join(", ").padEnd(layout_width)
      }
    })

    result += line_postfix;
    result += '\n';
  })

  return result;
}

function get_asm_path(id) {
  return path.join(__dirname, `temp${id}.asm`);
}

function get_bin_path(id) {
  return path.join(__dirname, `temp${id}.bin`);
}

function get_temp_path(id) {
  return path.join(__dirname, `temp${id}.txt`);
}

function write_file(path, data) {
  fs.writeFileSync(path, data);
};

function delete_file(path) {
  return fs.unlinkSync(path)
}

function read_file(path) {
  return fs.readFileSync(path, 'utf8');
};

function read_file_hex(path) {
  return fs.readFileSync(path, 'hex');
};

function execute(cmd) {
  return execSync(cmd, { encoding: 'utf8' });
}

async function write_file_async(filePath, data) {
  return fs.promises.writeFile(filePath, data);
}

async function delete_file_async(filePath) {
  return fs.promises.unlink(filePath);
}

async function read_file_async(filePath) {
  return fs.promises.readFile(filePath, 'utf8');
}

async function read_file_hex_async(filePath) {
  return fs.promises.readFile(filePath, 'hex');
}

module.exports = {
	apply_layout,
	calculate_layout,
	get_asm_path,
	get_bin_path,
	get_temp_path,
	write_file,
	delete_file,
	read_file,
	read_file_hex,
	execute,
	write_file_async,
	delete_file_async,
}
