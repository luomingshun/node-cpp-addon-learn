#include<node.h>
#include<v8.h>
#include<iostream>
namespace demo{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Exception;
using v8::Number;
using v8::Function;
using v8::FunctionTemplate;
using v8::MaybeLocal;
using v8::Boolean;
using v8::Array;
using v8::Context;

using std::cout;
using std::endl;

//普通函数返回值
void Hello(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    args.GetReturnValue().Set(String::NewFromUtf8(isolate,"world"));
}

//函数参数的使用
void Add(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong number of arguments")));
        return;
    }

    if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong arguments")));
        return;
    }

    double value = args[0]->NumberValue() + args[1]->NumberValue();
    Local<Number> num = Number::New(isolate,value); //对应为js的Number类型

    args.GetReturnValue().Set(num);
}

//回调函数
void RunCallback(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(!args[0]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong arguments")));
        return;
    }

    Local<Function> cb = Local<Function>::Cast(args[0]);
    const unsigned argc = 1;
    //Local<Value> argv[argc] = {String::NewFromUtf8(isolate,"hello world")}; //这种写法容易引起歧义
    //
    Local<Value> argv[argc];
    argv[0] = {String::NewFromUtf8(isolate,"hello world")};
    cb->Call(Null(isolate),argc,argv);
}

//对象返回
void CreateObject(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // if(args.Length() !=1 || !args[0]->IsString()) {
    //     isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong arguments")));
    //     return;
    // }

    Local<Object> obj = Object::New(isolate);
    obj->Set(String::NewFromUtf8(isolate,"msg"),args[0]->ToString());

    args.GetReturnValue().Set(obj);
}

//函数返回
void MyFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,"hello world!"));
}

void CreateFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,MyFunction);
    Local<Function> fn = tpl->GetFunction();
    //设置函数名
    fn->SetName(String::NewFromUtf8(isolate,"theFunction"));
    args.GetReturnValue().Set(fn);
}

//基本数据类型接口使用
void Test(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(args.Length() < 13) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong number of arguments")));
        return;
    }
    //Is函数的使用
    if(!args[0]->IsUndefined() || !args[1]->IsNull() || !args[2]->IsTrue() || !args[3]->IsFalse() || !args[4]->IsName() || 
        !args[5]->IsString() || !args[6]->IsSymbol() || !args[7]->IsFunction() || !args[8]->IsArray() || !args[9]->IsObject() ||
        !args[10]->IsBoolean() || !args[11]->IsNumber() || !args[12]->IsDate()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Wrong argument")));
        return;
    }

    // //To函数的使用
    // //MaybeLocal<String> a0 = args[0]->ToString();
    // //MaybeLocal<String> a1 = args[1]->ToString();
    // MaybeLocal<Boolean> a2 = args[2]->ToBoolean();
    // MaybeLocal<Boolean> a3 = args[3]->ToBoolean();
    // MaybeLocal<String> a4 = args[4]->ToString();
    // MaybeLocal<String> a5 = args[5]->ToString();
    // MaybeLocal<String> a6 = args[6]->ToString();
    // MaybeLocal<Object> a7 = args[7]->ToObject();
    // MaybeLocal<Array> a8 = args[8].As<Array>();
    // MaybeLocal<Object> a9 = args[9]->ToObject();
    // MaybeLocal<Boolean> a10 = args[10]->ToBoolean();
    // MaybeLocal<Number> a11 = args[11]->ToNumber(isolate); //这个较为特殊
    // MaybeLocal<String> a12 = args[12]->ToString();

        //To函数的使用
    Local<String> a0 = args[0]->ToString();
    Local<String> a1 = args[1]->ToString();
    Local<Boolean> a2 = args[2]->ToBoolean();
    Local<Boolean> a3 = args[3]->ToBoolean();
    Local<String> a4 = args[4]->ToString();
    Local<String> a5 = args[5]->ToString();
    Local<String> a6 = args[6]->ToString();
    //Local<Function> a7 = args[7].As<Function>();
    Local<Function> a7 = Local<Function>::Cast(args[7]);
    Local<Array> a8 = args[8].As<Array>();
    Local<Object> a9 = args[9]->ToObject();
    Local<Boolean> a10 = args[10]->ToBoolean();
    Local<Number> a11 = args[11]->ToNumber(isolate); //这个较为特殊
    Local<String> a12 = args[12]->ToString();

//    //Local<String>  b0   = a0.ToLocalChecked();  
//    //Local<String>  b1   = a1.ToLocalChecked(); 
//    Local<Boolean> b2   = a2.ToLocalChecked();
//    Local<Boolean> b3   = a3.ToLocalChecked(); 
//    Local<String>  b4   = a4.ToLocalChecked(); 
//    Local<String>  b5   = a5.ToLocalChecked(); 
//    Local<String>  b6   = a6.ToLocalChecked(); 
//    Local<Object>  b7   = a7.ToLocalChecked(); 
//    Local<Array>   b8   = a8.ToLocalChecked(); 
//    Local<Object>  b9   = a9.ToLocalChecked(); 
//    Local<Boolean> b10  = a10.ToLocalChecked(); 
//    Local<Number>  b11  = a11.ToLocalChecked(); 
//    Local<String>  b12  = a12.ToLocalChecked(); 

    //***************字符串操作******************************
   cout<<a4->Length()<<endl; //返回字符串长度
   cout<<a4->Utf8Length()<<endl; //返回字符串的Utf8长度
   cout<<a4->IsOneByte()<<endl;//该字符串是否只包含一个字节数据

    const char* str = "this is a string";
    //char*转string
    MaybeLocal<String> ms = String::NewFromUtf8(isolate,str);
    Local<String> s = ms.ToLocalChecked();

    //通过utf8value获取char*
    String::Utf8Value v(s);
    char *ret = *v;
    // string strstr(*);
    printf("char* = %s\n",ret);
    //****************************************************************

    //*************数值类型操作*************************************
    cout<<a11->Value()<<endl;
    //****************************************************************

    //*************数组操作*************
    cout<<a8->Length()<<endl;
    cout<<a8->Get(1)->ToNumber(isolate)->Value()<<endl;
    //*********************************

    //*************函数操作********

    String::Utf8Value name(a7->GetName()->ToString());
    cout<<*name<<endl;

    // Local<Context> context = isolate->GetCurrentContext();
    // Local<Value> b[1] = {};
    // Local<Value> x;
    // a7->Call(context,x,0,b);
    //*******************************

    //************对象操作*******************
    Local<Object> obj = Object::New(isolate);
    obj->Set(String::NewFromUtf8(isolate,"a4"),a4); //key-value
    // obj->Set(String::NewFromUtf8(isolate,"a11"),a11);
    // obj->Set(String::NewFromUtf8(isolate,"a8"),a8);
    // obj->Set(String::NewFromUtf8(isolate,"a7"),a7);
    //**************************************
    cout<<"--------------------"<<endl;
    //函数返回值
    args.GetReturnValue().Set(obj);
}


void init(Local<Object> exports) {
    NODE_SET_METHOD(exports,"hello",Hello);
    NODE_SET_METHOD(exports,"add",Add);
    NODE_SET_METHOD(exports,"callback",RunCallback);
    NODE_SET_METHOD(exports,"createobj",CreateObject);
    NODE_SET_METHOD(exports,"createfun",CreateFunction);
    NODE_SET_METHOD(exports,"test",Test);
}

NODE_MODULE(hello,init);

}