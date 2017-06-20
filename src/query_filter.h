#include<vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class queryFilter
{
public:
	int insert(char *str);
    int create(char *str);
    std::string getUrl(char *url);
    bool check(std::string *s);
private:
    std::vector<std::string> limit_arr;
};
