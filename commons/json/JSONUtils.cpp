#include "JSONUtils.h"
#include <string>
#include <fstream>

namespace json_utils {
	/**
	 * Function that transforms the string from the file received as parameter
	 * into a JSON
	 */
	json parseAsJson(const string &game_units_parameters_path) {
		fstream input_stream;
		input_stream.open(game_units_parameters_path, ios::in);
		string complete_json((istreambuf_iterator<char>(input_stream)),
							 istreambuf_iterator<char>());
		json json = json::parse(complete_json);
		input_stream.close();
		return json;
	}
}
