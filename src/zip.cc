#include <napi.h>
#include "zip.h"
#include <iostream>
#include <stdio.h>

class Zip : public Napi::ObjectWrap<Zip>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Zip(const Napi::CallbackInfo &info);
    ~Zip();

private:
    // static Napi::FunctionReference constructor;
    zip *file;
    Napi::Value ListFiles(const Napi::CallbackInfo &info);
    Napi::Value ReadFile(const Napi::CallbackInfo &info);
};

Napi::Object Zip::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "Zip", {InstanceMethod("ListFiles", &Zip::ListFiles), InstanceMethod("ReadFile", &Zip::ReadFile)});

    exports.Set("Zip", func);
    return exports;
}

Zip::Zip(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Zip>(info)
{
    if (info.Length() > 0)
    {
        std::string str = info[0].ToString().Utf8Value();

        this->file = zip_open(str.c_str(), ZIP_RDONLY, 0);
    }
    else
    {
        Napi::Error::Fatal("", "Requires a path");
    }
}
Zip::~Zip() {
    zip_close(file);
}

Napi::Value Zip::ListFiles(const Napi::CallbackInfo &info)
{
    int num = zip_get_num_files(this->file);

    Napi::Array arr = Napi::Array::New(info.Env(), num);
    for (int i = 0; i < num; i++)
    {
        arr[i] = Napi::String::New(info.Env(), zip_get_name(this->file, i, 0));
    }

    return arr;
}

Napi::Value Zip::ReadFile(const Napi::CallbackInfo &info)
{
    std::string fileName = info[0].ToString().Utf8Value();
    zip_file *f = zip_fopen(file, fileName.c_str(), 0);
    zip_stat_t st;
    zip_stat_init(&st);
    zip_stat(file, fileName.c_str(), 0, &st);

    char *buf = new char[st.size];
    bzero(buf, st.size);
    zip_fread(f, buf, st.size-1);
    auto string = Napi::String::New(info.Env(), buf);
    delete[] buf;
    return string;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    Zip::Init(env, exports);
    return exports;
}

NODE_API_MODULE(zip, InitAll)