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

module.exports = {
	apply_layout,
	calculate_layout
}
