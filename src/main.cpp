#include <iostream>
#include <vector>
#include <list>
#include "rapidjsonwrapper/rapidjsonwrapper.hpp"


int main() {
  std::string test_str = R"(
		{
			"server": {
				"ip": "192.168.0.0",
				"port": 32,
				"name": "test",
				"start": true,
        "list_test": [100, 99, 98, 97],
        "infos": [
          {
            "subserver": "182.32.12.25"
          }
        ]
			},
			"clients": [ "1", "2", "3", "4"]
		}
  )";

  // read
  RJSON_DOC(doc);
  RJSON_GET_ALLOC(doc, alloc);
  if (!RJSON_READ_DOC_FROM_STRING(doc, test_str)) {
    return 0;
  }
  if (RJSON_HAS_KEY(doc, "server")) {
    RJSON_GET_RAPID_VALUE(doc, "server", server_value);
    std::string ip, name;
    RJSON_GET_VALUE(server_value, "ip", ip);
    RJSON_GET_VALUE(server_value, "name", name);
    int port;
    RJSON_GET_VALUE(server_value, "port", port);
    bool start;
    RJSON_GET_VALUE(server_value, "start", start);
    std::list<int> list_test;
    RJSON_GET_VALUE(server_value, "list_test", list_test);
    RJSON_GET_RAPID_VALUE(server_value, "infos", infos_value);
    std::vector<std::string> subservers;
    for (int info_index = 0; info_index < infos_value.Size(); info_index++) {
      std::string subserver;
      RJSON_GET_VALUE(infos_value[info_index], "subserver", subserver);
      subservers.push_back(subserver);
    }
    std::cout << "ip:" << ip << std::endl
              << "port:" << port << std::endl
              << "name:" << name << std::endl
              << "start:" << start << std::endl;
    std::cout << "list_test:";
    for (auto &v : list_test) {
      std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "infos:";
    for (auto &subserver : subservers) {
      std::cout << subserver << " ";
    }
    std::cout << std::endl;
  }
  std::vector<std::string> client_values;
  if (RJSON_GET_VALUE(doc, "clients", client_values)) {
    std::cout << "clients:";
    for (auto &client_value : client_values) {
      std::cout << " " << client_value;
    }
    std::cout << std::endl;
  }

  // modify
  RJSON_GET_RAPID_VALUE(doc, "server", server_value);
  RJSON_DEL_VALUE(server_value, "ip");
  std::vector<int> add_vector = {10, 30, 50};
  RJSON_VALUE_ARRAY(array_test);
  for (auto &v : add_vector) {
    RJSON_ADD_ARRAY_VALUE(array_test, v, alloc);
  }
  RJSON_ADD_OBJ_VALUE(doc, "add1", "e", alloc);
  RJSON_ADD_OBJ_VALUE(doc, "add2", array_test, alloc);
  std::string result;
  RJSON_WRITE_DOC_TO_STRING_PRETTY(doc, result);
  std::cout << "result:" << result << std::endl;

  // new
  RJSON_DOC(new_doc);
  RJSON_GET_ALLOC(new_doc, new_alloc);
  RJSON_VALUE_ARRAY(images);
  for (int i = 0; i < 2; i++) {
    RJSON_VALUE_OBJ(image);
    RJSON_ADD_OBJ_VALUE(image, "base64", "dddd", new_alloc);
    RJSON_ADD_OBJ_VALUE(image, "roi", "eeee", new_alloc);
    RJSON_ADD_ARRAY_VALUE(images, image, new_alloc);
  }
  RJSON_ADD_OBJ_VALUE(new_doc, "images", images, new_alloc);

  std::list<std::string> add_strings = {"hello", "world"};
  RJSON_VALUE_ARRAY(hh);
  RJSON_ADD_ARRAY_VALUE(hh, add_strings, new_alloc);
  RJSON_ADD_OBJ_VALUE(new_doc, "hello_wold", hh, new_alloc);

  RJSON_WRITE_DOC_TO_STRING_PRETTY(new_doc, result);
  std::cout << "new result:\n" << result << std::endl;
  return 0;
}
