#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include<vector>
using std::vector;
class Page { 
public:
  Page(); //call all setters in the constructor
  //setters
    void set_id(int id);
    void set_url(string url);
    void set_rank(double rank);
    void set_links(vector<int> links);
    void set_walkers(int walkers);
  //getters
    int get_id();
    string get_url();
    double get_rank();
    vector<int>& get_links();
    int get_walkers();
  //increment/decrement walkers
    void add_walker();
    void sub_walker();
private:
  //Data members: id, url, pagerank, links , .. etc
    int pageid;
    string pageurl;
    double pagerank;
    vector<int> pagelinks;
    int pagewalkers;
};  
#endif
