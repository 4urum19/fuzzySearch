#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> getDirectories(std::string path) {
	std::vector<fs::directory_entry> dirs;

	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) {
			dirs.push_back(entry);
		}
	}

	return dirs;
}

std::regex globToRegex(std::string glob) {
	std::string regex_str = "^"; 

	for (char c : glob) {
		switch (c) {
		case '*':
			regex_str.append(".*");
			break;
		case '?':
			regex_str.push_back('.');
			break;
		case '.':
		case '+':
		case '^':
		case '$':
		case '\\': case '/':
		case '|':
		case '[': case ']':
		case '(': case ')':
		case '{': case '}':
			regex_str.push_back('\\');
			regex_str.push_back(c);
			break;
		default:
			regex_str.push_back(c);
			break;
		}
	}

	return std::regex(regex_str);
}

std::vector<fs::directory_entry> matchDirectories(std::vector<fs::directory_entry> dirs, std::regex regex) {
	std::vector<fs::directory_entry> result;

	std::copy_if(std::begin(dirs), std::end(dirs),
	    std::back_inserter(result),
	    [&](auto const& dir) {
	      return std::regex_match(dir.path().string(), regex);
	    }
  	);

  	return result;
}

fs::directory_entry menu(std::vector<fs::directory_entry> options) {
	int choice;

	std::cerr << "Select which directory to switch to:\n";
	for (std::size_t i = 0; i < options.size(); i += 1) {
		std::cerr << "	" << (i + 1) << ". " << options[i].path() << '\n';
	}
	std::cin >> choice;

	return options[(choice - 1)];
} 

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cerr << "No path/Argument is given\n";
		return -1;
	}

	const fs::path path = argv[1];
	if (!fs::exists(path) || !fs::is_directory(path)) {
		std::cerr << "Path is invalid\n";
		return -1;
	}

	std::vector<fs::directory_entry> dirs = getDirectories(argv[1]);

	std::string glob = path.string() + "/*" + argv[2] + "*";
	const std::regex regex = globToRegex(glob);
	std::vector<fs::directory_entry> matched = matchDirectories(dirs, regex);

	if (matched.size() == 0) {
		std::cerr << "Not found\n";
		return -1;
	} 

	fs::directory_entry result = matched[0];
	if (matched.size() > 1) {
		result = menu(matched);
	}

	std::cout << result.path().string() << '\n';

	return 0;
}