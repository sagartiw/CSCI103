#include "web.h"

Web::Web() 
{ 

}

Web::~Web() 
{ 

}

bool Web::read_graph(const char *filename) { 
    ifstream ifile(filename);
    if (ifile.fail()) { 
        return 0;
    }
    
    ifile >> numpages; //determine number of pages 
    
    if (ifile.fail()) { 
        return 0;
    }
    
    //Temps to pass through into individual pages
    int id;
    string url;
    double rank;
    vector<int> links;
    
    //need to figure out how to get the stream of links
    //use getline into a string then use stringstream
    string linkstore;
    stringstream linkstorestream;
    int separator;
    
    for (int i = 0; i < numpages; i++) {
        Page google;
        webpagelist.push_back(google);
        
        ifile >> id;
        ifile >> url;
        ifile >> rank;
        webpagelist[i].set_id(id);
        webpagelist[i].set_url(url);
        webpagelist[i].set_rank(rank);
        
        getline(ifile, linkstore); //runs through end of rank line
        getline(ifile, linkstore); //stores ids into a string
        linkstorestream << linkstore; //puts ids in stream to parse
        
        while(linkstorestream >> separator){
            links.push_back(separator);
        }
        webpagelist[i].set_links(links);
        
        links.clear(); //clears vector
        linkstorestream.clear(); //clears stringstream
    }
    
    ifile.close();
    return 1; //Successful if I made it this far
}

bool Web::write_graph(const char *filename)
{ 
    ofstream ofile(filename); 
    if (ofile.fail()) {
        return 0;
    }
    
    ofile << numpages << endl;//print out num pages at top
    
    for (int i = 0; i < numpages; i++) { //print out each page
        ofile << webpagelist[i].get_id() << endl;
        ofile << '\t' << webpagelist[i].get_url() << endl; 
        ofile << '\t' << webpagelist[i].get_rank() << endl;
        ofile << '\t';
        
        for(unsigned int j = 0; j < webpagelist[i].get_links().size(); j++){
            vector<int> printer = webpagelist[i].get_links();
            ofile << printer[j] << " ";
        }
        ofile << endl;
    }
    
    ofile.close();
    return 1;
}

void Web::calculate_rank(int S,int N)
{
    int initialwalkers = N/numpages;
    for(int i = 0; i < numpages; i++){ //Initializes all pages with equal walkers
        webpagelist[i].set_walkers(initialwalkers);
    }
    
    for(int i = 1; i <= S; i++){ 
        vector<int> originalwalker;
        for(int j = 0; j < numpages; j++){ //Ensures walkers move only once per sim
            int temp = webpagelist[j].get_walkers();
            originalwalker.push_back(temp);
        }
        
        for(int j = 0; j < numpages; j++){
            for(int k = 0; k < originalwalker[j]; k++){
                int size = webpagelist[j].get_links().size();
                int index = rand() % size; //Used to select single walker in vector
                int dest = (webpagelist[j].get_links())[index];
                webpagelist[dest].add_walker(); //Add walker to destination
                webpagelist[j].sub_walker(); //Subtract walker from origin
            }
        }
    }
    
    for (int i = 0; i < numpages; i++) {
        int walkercount = webpagelist[i].get_walkers();
        double rank = ((double)walkercount)/N; //Proportion of walkers per page
        webpagelist[i].set_rank(rank); 
    } 
}
