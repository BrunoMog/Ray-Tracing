#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

class Json {
public:
    using array_t = std::vector<Json>;
    using object_t = std::map<std::string, Json>;

    Json();
    Json(std::nullptr_t);
    Json(bool b);
    Json(double d);
    Json(int i);
    Json(long long i);
    Json(const std::string& s);
    Json(std::string&& s);
    Json(const char* s);
    Json(const array_t& a);
    Json(array_t&& a);
    Json(const object_t& o);
    Json(object_t&& o);

    bool isNull() const;
    bool isBool() const;
    bool isNumber() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

    bool asBool() const;
    double asNumber() const;
    const std::string& asString() const;
    const array_t& asArray() const;
    const object_t& asObject() const;

    array_t& asArray();
    object_t& asObject();
    const Json& at(const std::string& key) const;
    const Json& operator[](const std::string& key) const;
    const Json& operator[](size_t i) const;

    bool contains(const std::string& key) const;
    size_t size() const;

private:
    std::variant<std::nullptr_t, bool, double, std::string, array_t, object_t> data;
};

class JsonParser {
public:
    Json parseFile(const std::string& filename);
    Json parseString(const std::string& text);

private:
    std::string src;
    size_t pos = 0;
    int line = 1;
    int col = 1;

    bool eof() const;
    char peek(size_t off = 0) const;
    char advance();

    [[noreturn]] void error(const std::string& msg) const;
    void expect(char c);
    void skipIgnored();

    Json parseValue();
    Json parseObject();
    Json parseArray();
    Json parseLiteral();
    Json parseNumber();

    static int hexValue(char c);
    static void appendUtf8(std::string& out, uint32_t cp);
    uint32_t parseHex4();
    std::string parseStringLiteral();
};
