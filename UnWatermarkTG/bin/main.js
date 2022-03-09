//const readline = require('readline');
import { debug } from 'console';
import * as fs from 'fs';
import * as rl from 'readline'

const cin = rl.createInterface({
    input: process.stdin,
    output: process.stdout
  });
  
fs.readFile(process.argv[2], 'utf8', (err, data) => {
    if (err) {
        console.error(err)
        return
    }
    var json = JSON.parse(data);
    
    console.log(json);
    console.log(`Deleting objects, containing propert of ${process.argv[3]}`);
    var new_json = {};
    
    for(var obj in json)
    {
        CheckForDelete(new_json, obj, json[obj], process.argv[3])
    }

    var new_json_str = JSON.stringify(new_json);
    fs.writeFile('./new.json', new_json_str, {}, (err) => {
        if (err) throw err;
        console.log('File saved succesfully');
    });  
    cin.close();
});
    
  


  function CheckForDelete(parent, key, object, string)
  {
    //console.log(`CFD FOR ${key}:${object}`)

    var is_arr = Array.isArray(object)
    var is_obj = (typeof object === "object")

    //console.log(`OBJECT : ${is_obj}; ARRAY : ${is_arr}`)

    if (is_arr)
        var new_arr = []
    else if (is_obj)
        var new_obj = {}
    var contains = false
    if (is_obj)
        for(var obj in object)
        {
            //console.log(`${obj}:${object[obj]}`)
            if (typeof object[obj] === "object")
            {
                if (is_arr)
                {
                    if (CheckForDelete(new_arr, obj, object[obj], string) == true)
                        contains = true
                }
                else
                {
                    if (CheckForDelete(new_obj, obj, object[obj], string) == true)
                        contains = true
                }
            }
            else if (object[obj].toString().includes(string))
            {
                console.log(`${object[obj]} contains ${string}`);
                contains = true
            }
            else
            {
                if (is_arr)
                    new_arr.push(object[obj])
                else
                    new_obj[obj] = object[obj]
            }
        }
    if (!contains)  //Включение в копию json'а
    {
        if (Array.isArray(parent))
        {
            if (is_arr)
                parent.push(new_arr)
            else if (is_obj)
                parent.push(new_obj)
        }
        else
        {
            if (is_arr)
                parent[key] = new_arr;
            else if (is_obj)
                parent[key] = new_obj
            else
                parent[key] = object
        }
    }
    return false;
  } 