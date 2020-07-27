#include "page.h"

Page::Page(){
   //Keeping blank in favor of having 
   //individual setters/getters
}

void Page::set_id(int id){
    pageid = id;
}

void Page::set_url(string url){
    pageurl = url;
}

void Page::set_rank(double rank){
    pagerank = rank;
}

void Page::set_links(vector<int> links){
    pagelinks = links;
}

void Page::set_walkers(int walkers){
    pagewalkers = walkers;
}

int Page::get_id(){
    return pageid;
}

string Page::get_url(){
    return pageurl;
}

double Page::get_rank(){
    return pagerank;
}

vector<int>& Page::get_links(){
    return pagelinks;
}

int Page::get_walkers(){
    return pagewalkers;
}

void Page::add_walker(){
    pagewalkers++;
}

void Page::sub_walker(){
    pagewalkers--;
}