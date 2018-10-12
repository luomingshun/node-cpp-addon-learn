var addon = require("../build/Release/hello")

//函数基本返回
var str = addon.hello()
console.log(str)

//函数参数
var num = addon.add(1,1.0)
console.log(num)

//回调函数
addon.callback(function(msg){
    console.log(msg)
})

//对象返回
var obj = addon.createobj("123")
console.log(obj)
var obj1 = addon.createobj(null)
console.log(obj1)
var obj2 = addon.createobj(function() {})
console.log(obj2)

//函数返回
var fun = addon.createfun();
console.log(fun.name)
console.log(fun())

//基本数据类型的使用
var sym = Symbol("sym")
var func = function() {
    console.log("1111 hello world!")
}
var arr = new Array()
arr[0] = 1
arr[1] = 2
arr[2] = 3

var person = new Object();
person.name = "alan"
person.age = 22
person.address = 'nanjing'

var date = new Date()

var obj = addon.test(undefined,null,true,false,"aaa","this is a string",sym,func,arr,person,true,11.1,date)
console.log(obj)