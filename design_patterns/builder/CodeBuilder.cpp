#include <string>
#include <ostream>
#include <vector>
#include <utility>
using namespace std;

/* 
Design Patterns in Modern C++
Builder Coding Exercise
 */
class CodeBuilder
{
private:
    string class_name{};
    vector<pair<string, string>> fields{};
public:
  CodeBuilder(const string& class_name)
  {
      // todo
      this->class_name = class_name;
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    fields.emplace_back(make_pair(type, name));
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    // todo
    os << "class " << obj.class_name << "\n"
    << "{" << "\n";
    for( auto& p : obj.fields) {
        os << "  " << p.first << " " << p.second << ";\n";
    }
    os << "};";
    
    return os;
  }
};