#ifndef INCLUDE_RAPIDJSONWRAPPER_RAPIDJSONWRAPPER_HPP_
#define INCLUDE_RAPIDJSONWRAPPER_RAPIDJSONWRAPPER_HPP_

#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"

static bool ReadDocFromFile(rapidjson::Document &doc,
                            const std::string &file_path) {
  std::ifstream ifs(file_path.c_str());
  if (!ifs.is_open()) {
    return false;
  }
  rapidjson::IStreamWrapper isw(ifs);
  rapidjson::ParseResult ok = doc.ParseStream(isw);
  return ok ? true : false;
}

static bool ReadDocFromString(rapidjson::Document &doc,
                              const std::string &json_str) {
  rapidjson::ParseResult ok = doc.Parse(json_str.c_str());
  return ok ? true : false;
}

static bool WriteDocToFile(const rapidjson::Document &doc,
                           const std::string &file_path) {
  std::ofstream ofs(file_path.c_str());
  if (!ofs.is_open()) {
    return false;
  }
  rapidjson::OStreamWrapper osw(ofs);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
  return doc.Accept(writer);
}

static bool WriteDocToString(const rapidjson::Document &doc,
                             std::string &doc_string) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  if (doc.Accept(writer)) {
    doc_string = buffer.GetString();
    return true;
  }
  return false;
}

static bool WriteDocToFilePretty(const rapidjson::Document &doc,
                                 const std::string &file_path) {
  std::ofstream ofs(file_path.c_str());
  if (!ofs.is_open()) {
    return false;
  }
  rapidjson::OStreamWrapper osw(ofs);
  rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
  return doc.Accept(writer);
}

static bool WriteDocToStringPretty(const rapidjson::Document &doc,
                                   std::string &doc_string) {
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  if (doc.Accept(writer)) {
    doc_string = buffer.GetString();
    return true;
  }
  return false;
}

static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  int32_t &value) {
  if (rapid_value[key.c_str()].IsInt()) {
    value = rapid_value[key.c_str()].GetInt();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  uint32_t &value) {
  if (rapid_value[key.c_str()].IsUint()) {
    value = rapid_value[key.c_str()].GetUint();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  int64_t &value) {
  if (rapid_value[key.c_str()].IsInt64()) {
    value = rapid_value[key.c_str()].GetInt64();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  uint64_t &value) {
  if (rapid_value[key.c_str()].IsUint64()) {
    value = rapid_value[key.c_str()].GetUint64();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  float &value) {
  if (rapid_value[key.c_str()].IsFloat()) {
    value = rapid_value[key.c_str()].GetFloat();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  double &value) {
  if (rapid_value[key.c_str()].IsDouble()) {
    value = rapid_value[key.c_str()].GetDouble();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  bool &value) {
  if (rapid_value[key.c_str()].IsBool()) {
    value = rapid_value[key.c_str()].GetBool();
    return true;
  }
  return false;
}
static bool GetObjectValueWrapper(const rapidjson::Value &rapid_value,
                                  const std::string &key,
                                  std::string &value) {
  if (rapid_value[key.c_str()].IsString()) {
    value = rapid_value[key.c_str()].GetString();
    return true;
  }
  return false;
}

template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<int32_t> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsInt()) {
      values.push_back(iter->GetInt());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<uint32_t> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsUint()) {
      values.push_back(iter->GetUint());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<int64_t> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsInt64()) {
      values.push_back(iter->GetInt64());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<uint64_t> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsUint64()) {
      values.push_back(iter->GetUint64());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<float> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsFloat()) {
      values.push_back(iter->GetFloat());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<double> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsDouble()) {
      values.push_back(iter->GetDouble());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<bool> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsBool()) {
      values.push_back(iter->GetBool());
    } else {
      return false;
    }
  }
  return true;
}
template<template<typename T, typename Allocator = std::allocator<T>> class Container>
static bool GetArrayValueWrapper(const rapidjson::Value &rapid_value,
                          Container<std::string> &values) {
  for (rapidjson::Value::ConstValueIterator iter = rapid_value.Begin();
       iter != rapid_value.End(); ++iter) {
    if (iter->IsString()) {
      values.push_back(iter->GetString());
    } else {
      return false;
    }
  }
  return true;
}

template <typename T, template<typename v, typename Allocator = std::allocator<v>> class Container>
static bool GetValue(const rapidjson::Value &rapid_value,
              const std::string &key,
              Container<T> &values) {
  if (rapid_value.IsObject() && rapid_value.HasMember(key.c_str())) {
    const rapidjson::Value &value_array = rapid_value[key.c_str()];
    if (value_array.IsArray()) {
      return GetArrayValueWrapper(value_array, values);
    }
  }
  return false;
}

template <typename T>
static bool GetValue(const rapidjson::Value &rapid_value,
              const std::string &key,
              T &value) {
  if (rapid_value.IsObject() && rapid_value.HasMember(key.c_str())) {
    return GetObjectValueWrapper(rapid_value, key, value);
  }
  return false;
}

template <typename T>
bool AddObjectValueWrapper(rapidjson::Value &rapid_value,
                           const std::string &key,
                           const T &value,
                           rapidjson::Document::AllocatorType &alloc) {
  if (!rapid_value.HasMember(key.c_str())) {
    rapid_value.AddMember(rapidjson::Value(key.c_str(), alloc).Move(),
                          rapidjson::Value(value).Move(), alloc);
    return true;
  }
  return false;
}

template <typename T>
bool AddArrayValueWrapper(rapidjson::Value &rapid_value,
                           const T &value,
                           rapidjson::Document::AllocatorType &alloc) {
  if (rapid_value.IsArray()) {
    rapid_value.PushBack(value, alloc);
    return true;
  }
  return false;
}

template <>
bool AddObjectValueWrapper(rapidjson::Value &rapid_value,
                           const std::string &key,
                           const rapidjson::Value &value,
                           rapidjson::Document::AllocatorType &alloc) {
  if (!rapid_value.HasMember(key.c_str())) {
    rapid_value.AddMember(rapidjson::Value(key.c_str(), alloc).Move(),
                          rapidjson::Value(value, alloc), alloc);
    return true;
  }
  return false;
}

template <>
bool AddObjectValueWrapper<std::string>(rapidjson::Value &rapid_value,
                                        const std::string &key,
                                        const std::string &value,
                                        rapidjson::Document::AllocatorType &alloc) {
  if (!rapid_value.HasMember(key.c_str())) {
    rapid_value.AddMember(rapidjson::Value(key.c_str(), alloc).Move(),
                          rapidjson::Value(value.c_str(), alloc).Move(), alloc);
    return true;
  }
  return false;
}

template <>
bool AddArrayValueWrapper(rapidjson::Value &rapid_value,
                          const std::string &value,
                          rapidjson::Document::AllocatorType &alloc) {
  if (rapid_value.IsArray()) {
    rapid_value.PushBack(rapidjson::Value(value.c_str(), alloc).Move(), alloc);
    return true;
  }
  return false;
}

template <>
bool AddArrayValueWrapper(rapidjson::Value &rapid_value,
                          const rapidjson::Value &value,
                          rapidjson::Document::AllocatorType &alloc) {
  if (rapid_value.IsArray()) {
    rapid_value.PushBack(rapidjson::Value(value, alloc), alloc);
    return true;
  }
  return false;
}

template <typename T, template<typename v, typename Allocator = std::allocator<v>> class Container>
static bool AddArrayValueWrapper(rapidjson::Value &rapid_value,
                          const Container<T> &values,
                          rapidjson::Document::AllocatorType &alloc) {
  if (rapid_value.IsArray()) {
    for (auto &value : values) {
      rapid_value.PushBack(value, alloc);
    }
    return true;
  }
  return false;
}

template <template<typename v, typename Allocator = std::allocator<v>> class Container>
static bool AddArrayValueWrapper(rapidjson::Value &rapid_value,
                          const Container<std::string> &values,
                          rapidjson::Document::AllocatorType &alloc) {
  if (rapid_value.IsArray()) {
    for (auto &value : values) {
      rapid_value.PushBack(
          rapidjson::Value(value.c_str(), alloc).Move(), alloc);
    }
    return true;
  }
  return false;
}

static bool DelObjectValue(rapidjson::Value &rapid_value,
                           const std::string &key) {
  if (rapid_value.HasMember(key.c_str())) {
    return rapid_value.RemoveMember(key.c_str());
  }
  return false;
}

#define RJSON_DOC(doc) \
        rapidjson::Document doc; \
        doc.SetObject()
#define RJSON_VALUE_OBJ(value) \
        rapidjson::Value value(rapidjson::kObjectType)
#define RJSON_VALUE_ARRAY(value) \
        rapidjson::Value value(rapidjson::kArrayType)
#define RJSON_ITERAROT(iter) \
        rapidjson::Value::ConstValueIterator iter
#define RJSON_GET_ALLOC(doc, alloc) \
        rapidjson::Document::AllocatorType& alloc = doc.GetAllocator()
#define RJSON_READ_DOC_FROM_FILE(doc, filepath) \
        ReadDocFromFile(doc, filepath)
#define RJSON_READ_DOC_FROM_STRING(doc, string_value) \
        ReadDocFromString(doc, string_value)
#define RJSON_WRITE_DOC_TO_FILE(doc, filepath) \
        WriteDocToFile(doc, filepath)
#define RJSON_WRITE_DOC_TO_STRING(doc, string_value) \
        WriteDocToString(doc, string_value)
#define RJSON_WRITE_DOC_TO_FILE_PRETTY(doc, filepath) \
        WriteDocToFilePretty(doc, filepath)
#define RJSON_WRITE_DOC_TO_STRING_PRETTY(doc, string_value) \
        WriteDocToStringPretty(doc, string_value)
#define RJSON_HAS_KEY(rapid_value, key) \
        rapid_value.HasMember(key)
#define RJSON_GET_VALUE(rapid_value, key, value) \
        GetValue(rapid_value, key, value)
#define RJSON_GET_RAPID_VALUE(rapid_value, key, value) \
        rapidjson::Value &value = rapid_value[key]
#define RJSON_ADD_OBJ_VALUE(rapid_value, key, value, alloc) \
        AddObjectValueWrapper(rapid_value, key, value, alloc)
#define RJSON_ADD_ARRAY_VALUE(rapid_value, value, alloc) \
        AddArrayValueWrapper(rapid_value, value, alloc)
#define RJSON_DEL_VALUE(rapid_value, key) \
        DelObjectValue(rapid_value, key)
#endif  // INCLUDE_RAPIDJSONWRAPPER_RAPIDJSONWRAPPER_HPP_

