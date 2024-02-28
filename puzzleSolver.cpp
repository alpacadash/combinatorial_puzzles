#include "puzzleSolver.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <set>


void updateSet(std::set<char>& characters, std::string s) {
  for(unsigned int i=0;i<s.length();i++)
    characters.insert(s[i]);


bool verifySolution(const std::string& addend1, const std::string& addend2,
                    const std::string& result,
                    const std::unordered_map<char, unsigned>& mapping) {
    // TODO: Implement

    int a = 0;
    int b = 0;
    int c = 0;

    for(char ch : addend1){
        a = a*10 + mapping.at(ch);

    }



    for(char ch : addend2){
        b = b*10 + mapping.at(ch);

    }



    for(char ch : result){
        c = c*10 + mapping.at(ch);

    }

    return (a+b == c);  // FYI, this stub is not a correct solution.
}


bool solveRecursive(std::string addend1, std::string addend2, std::string sum, std::set<char>& characters, std::unordered_map<char, unsigned>& mapping, std::unordered_map<unsigned, char>& invertedMapping, int index) {
  int charSize = characters.size();
  if(index==charSize)
    return verifySolution(addend1,addend2,sum,mapping);

  std::set<char>::iterator it=characters.begin();
  bool status;
  std::advance(it,index);

  for(int i=0;i<10;i++) {
	if(invertedMapping.find(i)!=invertedMapping.end())
      continue;

    mapping[*it]=i;
    invertedMapping[i]=*it;
    status = solveRecursive(addend1,addend2,sum,characters,mapping,invertedMapping,index+1);

    if(status)
      return status;

    invertedMapping.erase(i);
  }
  mapping.erase(*it);

  return false;
}

bool puzzleSolver(const std::string& addend1, const std::string& addend2,
                  const std::string& sum,
                  std::unordered_map<char, unsigned>& mapping) {
    // TODO: Implement this
    std::set<char> characters;
    updateSet(characters,addend1);
    updateSet(characters, addend2);
    updateSet(characters, sum);
    if(characters.size() > 10)
    {
        return false;
    }
    std::unordered_map<unsigned, char> invertedMapping;


    return solveRecursive(addend1, addend2, sum, characters, mapping, invertedMapping, 0);  // This is not the correct general solution.
}
