"use strict"

const https = require('https');
const { json } = require('stream/consumers');

const url = "https://asmjit.com/asmgrid/lib/asmdb/isa_x86.json";

https.get(url, res => {
    let data = [];
    res.on('data', chunk => {
        data.push(chunk);
    });
  
    res.on('end', () => {
        parse_instructions(JSON.parse(Buffer.concat(data).toString()).instructions);
    });
  }).on('error', err => {
    console.log('Error: ', err.message);
});

function parse_instructions(instructions) {
    let result = [];

    instructions.forEach(category => {
        category.data.forEach(inst => {
            console.log(inst.inst);
        })
    });
}