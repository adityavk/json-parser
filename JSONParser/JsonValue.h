//
//  JsonValue.h
//  JSONParser
//
//  Created by Aditya Vikram on 18/03/21.
//

#ifndef JsonValue_h
#define JsonValue_h

#include <unordered_map>
#include <variant>
#include <optional>
#include <iostream>

namespace JSONParser {

constexpr bool shouldPrintValueTypes = false;

template<typename TValue>
class GenericObject {
    std::unordered_map<std::string, TValue> members_;
public:
    GenericObject() = default;
    
    bool exists(const std::string& key) const {
        return members_.find(key) != members_.end();
    }
    
    TValue getValue(const std::string& key) const {
        return members_.at(key);
    }
    
    std::optional<TValue> getOptValue(const std::string& key) const {
        if (auto it = members_.find(key); it != members_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    void setMember(const std::string& key, const TValue& value) {
        members_.insert_or_assign(key, value);
    }
    
    void removeMember(const std::string& key) {
        members_.erase(key);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const GenericObject& object) {
        os << "{\n";
        for (const auto& [key, value] : object.members_) {
            os << key << ": " << value << ",\n";
        }
        os << "}";
        return os;
    }
};

template<typename TValue>
class GenericArray {
    std::vector<TValue> members_;
public:
    GenericArray() = default;
    
    size_t size() const { return members_.size(); }
    
    TValue& operator[](size_t pos) { return members_[pos]; }
    const TValue& operator[](size_t pos) const { return members_[pos]; }
    
    void addMember(const TValue& value) {
        members_.push_back(value);
    }
    
    void removeMember(const TValue& value) {
        members_.erase(value);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const GenericArray& array) {
        os << "[\n";
        for (const auto& value : array.members_) {
            os << value << ",\n";
        }
        os << "]";
        return os;
    }
};

class JSONValue {
    using Object = GenericObject<JSONValue>;
    using Array = GenericArray<JSONValue>;
    std::variant<std::monostate, std::string, double, uint64_t, bool, Object, Array> value_;
public:
    JSONValue() = default;
    JSONValue(const std::string& string): value_(string) {}
    JSONValue(const char* cStr): value_(std::string(cStr)) {}
    JSONValue(const double num): value_(num) {}
    JSONValue(const uint64_t num): value_(num) {}
    JSONValue(const bool boolean): value_(boolean) {}
    JSONValue(const Object& object): value_(object) {}
    JSONValue(const Array& array): value_(array) {}
    
    bool isNull() const {  return value_.index() == 0; }
    bool isString() const {  return value_.index() == 1; }
    bool isDouble() const {  return value_.index() == 2; }
    bool isInteger() const {  return value_.index() == 3; }
    bool isBool() const {  return value_.index() == 4; }
    bool isObject() const {  return value_.index() == 5; }
    bool isArray() const {  return value_.index() == 6; }
    
    const std::string& getString() const {  return std::get<std::string>(value_); }
    double getDouble() const {  return std::get<double>(value_); }
    uint64_t getInteger() const {  return std::get<uint64_t>(value_); }
    bool getBool() const {  return std::get<bool>(value_); }
    const Object& getObject() const {  return std::get<Object>(value_); }
    const Array& getArray() const {  return std::get<Array>(value_); }
    
    std::optional<std::string> getOptString() const {
        if (isString()) return getString();
        return std::nullopt;
    }
    
    std::optional<double> getOptDouble() const {
        if (isDouble()) return getDouble();
        return std::nullopt;
    }
    
    std::optional<uint64_t> getOptInteger() const {
        if (isInteger()) return getInteger();
        return std::nullopt;
    }
    
    std::optional<bool> getOptBool() const {
        if (isBool()) return getBool();
        return std::nullopt;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const JSONValue& value) {
        if (value.isNull()) {
            os << "(null)";
        } else if (value.isString()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Str) ";
            }
            os << value.getString();
        } else if (value.isDouble()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Double) ";
            }
            os << value.getDouble();
        } else if (value.isInteger()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Int) ";
            }
            os << value.getInteger();
        } else if (value.isBool()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Bool) ";
            }
            os << value.getBool();
        } else if (value.isObject()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Obj) ";
            }
            os << value.getObject();
        } else if (value.isArray()) {
            if constexpr (shouldPrintValueTypes) {
                os << "(Arr) ";
            }
            os << value.getArray();
        }
        return os;
    }
};

using JSONObject = GenericObject<JSONValue>;
using JSONArray = GenericArray<JSONValue>;

}


#endif /* JsonValue_h */
