int main() {
  std::ifstream file("a.txt");
  std::stringstream ss;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      ss << line << '\n';
    }
    file.close();
    std::string file_contents = ss.str();
    std::cout << file_contents << std::endl;
  }

  // save
  std::streambuf* original_cin = std::cin.rdbuf();
  std::cin.rdbuf(ss.rdbuf());

  char c = 0xcc;
  while (!std::cin.eof()) {

    // cin会跳过换行
    //std::cin >> c;
    
    // cin.get不会跳过换行
    c = std::cin.get();
    std::cout << c; 
  }
  // restore
  std::cin.rdbuf(original_cin);

  return 0;
}
