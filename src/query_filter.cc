 #include "query_filter.h"

int queryFilter::create(char *str) {
    std::string str_data = str;
    boost::split(limit_arr, str_data, boost::is_any_of(","));
    return 0;
}

int queryFilter::insert(char *str) {
    std::string str_data = str;
    limit_arr.push_back(str_data);
    return 0;
}

std::string queryFilter::getUrl(char *url) {
    std::string str_url = url;

    std::vector<std::string> str_arr, query_arr, ret_arr;
    boost::split(str_arr, str_url, boost::is_any_of("?"));

    if (str_arr.size() < 2) {
        return str_url;
    }

    if (limit_arr.size() == 0 ) {
        return str_url;
    }

    std::string ret = str_arr[0];
    std::string query = str_arr[1];
    boost::split(query_arr, query, boost::is_any_of("&"));

    if (query_arr.size() == 0) {
        return str_url;
    }

     int nSize = query_arr.size();  

     for(int i = 0; i < nSize; i++) {
        if (this->check(&(query_arr[i]))) {
            ret_arr.push_back(query_arr[i]);
        }
     }

     if (ret_arr.size() == 0) {
        return url;
     }

     ret += "?";
     ret += ret_arr[0];

     for (int i =1; i< ret_arr.size(); i++) {
        ret += "&";
        ret += ret_arr[i];
     }

     return ret;
}

bool queryFilter::check(std::string *s) {
    std::vector<std::string> str_arr;
    boost::split(str_arr, *s, boost::is_any_of("="));

    if (str_arr.size() <= 0) {
        return false;
    }

    std::string key = str_arr[0];

    std::vector<std::string>::iterator iter=std::find(limit_arr.begin(),limit_arr.end(),key);

    if (iter == limit_arr.end()) {
        return false;
    }

    return true;
}
