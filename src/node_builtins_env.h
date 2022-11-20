#ifndef SRC_NODE_BUILTINS_ENV_H_
#define SRC_NODE_BUILTINS_ENV_H_

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include "node_builtins.h"

namespace node {
class Environment;
class ExternalReferenceRegistry;

namespace builtins {

extern const bool has_code_cache;

class BuiltinEnv {
 public:
  static void RegisterExternalReferences(ExternalReferenceRegistry* registry);
  static void Initialize(v8::Local<v8::Object> target,
                         v8::Local<v8::Value> unused,
                         v8::Local<v8::Context> context,
                         void* priv);

  static v8::MaybeLocal<v8::Function> LookupAndCompile(
      v8::Local<v8::Context> context,
      const char* id,
      std::vector<v8::Local<v8::String>>* parameters,
      Environment* optional_env);

  static v8::Local<v8::Object> GetSourceObject(v8::Local<v8::Context> context);
  // Returns config.gypi as a JSON string
  static v8::Local<v8::String> GetConfigString(v8::Isolate* isolate);
  static bool Exists(const char* id);
  static bool Add(const char* id, const UnionBytes& source);

  // Loads data into BuiltinLoader::.instance.code_cache_
  // Generated by mkcodecache as node_code_cache.cc when
  // the build is configured with --code-cache-path=.... They are noops
  // in node_code_cache_stub.cc
  static void InitializeCodeCache();

 private:
  static void RecordResult(const char* id,
                           BuiltinLoader::Result result,
                           Environment* env);
  static void GetModuleCategories(
      v8::Local<v8::Name> property,
      const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetCacheUsage(const v8::FunctionCallbackInfo<v8::Value>& args);
  // Passing ids of builtin module source code into JS land as
  // internalBinding('builtins').builtinIds
  static void ModuleIdsGetter(v8::Local<v8::Name> property,
                              const v8::PropertyCallbackInfo<v8::Value>& info);
  // Passing config.gypi into JS land as internalBinding('builtins').config
  static void ConfigStringGetter(
      v8::Local<v8::Name> property,
      const v8::PropertyCallbackInfo<v8::Value>& info);
  // Compile a specific native module as a function
  static void CompileFunction(const v8::FunctionCallbackInfo<v8::Value>& args);
};

}  // namespace builtins

}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // SRC_NODE_BUILTINS_ENV_H_