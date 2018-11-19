#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;


//Function that removes the dots from the IP address input.
string removedots(string input)
{
    
    size_t dotloc = input.find('.');
    
    //The addition of 0s is in order to set all the octets to 3 digits so that when the comparison for range is done, they compare the correct octets.
    if(dotloc < 3)
    {
        while(input.find('.') != 3)
        {
            input.insert(0,"0");
        }
        dotloc = input.find('.');
    }
    
    dotloc = input.find('.',4);
    
    if(dotloc < 7)
    {
        while(input.find('.',4) != 7)
        {
            input.insert(4,"0");
        }
        dotloc = input.find('.',4);
    }
    
    dotloc = input.find('.',8);
    
    if(dotloc < 11)
    {
        while(input.find('.',8) != 11)
        {
            input.insert(8,"0");
        }
        dotloc = input.find('.',8);
    }
    
    while(input.substr(12).size() < 3)
    {
        input.insert(12,"0");
    }
    
    
    while(input.find('.') != string::npos)
    {
        size_t dotloc = input.find('.');
        
        input.erase(input.begin() + dotloc);
    }
    
    return input;
}


//Struct that contains all the values for a rule
struct Rule
{
    //Using bool and unsigned ints for saving on memory for large datasets
    bool direction; //inbound = true, outbound = false
    bool protocol; //tcp = true, udp = false
    
    unsigned int port_lower_end;
    unsigned int port_upper_end;
    
    long octet_lower_end;
    long octet_upper_end;
    
    //constructor
    Rule(string in)
    {
        //Spliting the string based on commas. (Unnecessarily convoluted step resulted from using C++)
        size_t commaloc = in.find(',');
        string dir = in.substr(0,commaloc);
        
        //Setting direction
        if(dir == "inbound")
            this->direction = true;
        else
            this->direction = false;
        
        size_t commaloc2 = in.find(',', commaloc+1);
        string ptcl = in.substr(commaloc+1,commaloc2-commaloc - 1);
        
        //Setting protocol
        if(ptcl == "tcp")
            this->protocol = true;
        else
            this->protocol = false;
        
        size_t commaloc3 = in.find(',', commaloc2+1);
        string port = in.substr(commaloc2+1,commaloc3-commaloc2 - 1);
        
        //Setting Port
        //In case of range involved
        if(port.find('-') != string::npos)//there is a range involved
        {
            size_t dashloc = port.find('-');
            string lowend = port.substr(0, dashloc);
            string upend = port.substr(dashloc+3);
            this->port_lower_end = stoi(lowend);
            
            this->port_upper_end = stoi(upend);
        }
        //In case there is no range involved
        else
        {
            this->port_lower_end = stoi(port);
            this->port_upper_end = stoi(port);
        }
        
        
        //Setting IP address
        
        string ipaddress = in.substr(commaloc3+1);
        
        //Checking if a range is involved
        if(ipaddress.find('-') != string::npos)//there is a range involved
        {
            size_t dashloc = ipaddress.find('-');
            string lowend = ipaddress.substr(0, dashloc);
            string upend = ipaddress.substr(dashloc+3);
            
            octet_lower_end = stol(removedots(lowend));
            octet_upper_end = stol(removedots(upend));
            
            
        }
        //Normal case
        else
        {
            octet_lower_end = stol(removedots(ipaddress));
            octet_upper_end = stol(removedots(ipaddress));
        }
        
        
    }
    
    //Checks if an input rule matches with the current rule
    bool is_match(string direction, string protocol, int port, string ip_address)
    {
        //int to check if all the conditions are satisfied && returns false immediately if any condition does not satisfy the condition
        int checked = 0;
        
        //Checking if all the parameters match with the current rule.
        
        if((direction == "inbound" && this->direction) || (direction == "outbound" && !this->direction))
            checked++;
        else
            return false;
        
        if((protocol == "tcp" && this->protocol) || (protocol == "udp" && !this->protocol))
            checked++;
        else
            return false;
        
        if((port <= port_upper_end) && (port >= port_lower_end))
            checked++;
        else
            return false;
        
        if((this->octet_lower_end <= stol(removedots(ip_address)))&&((this->octet_upper_end >= stol(removedots(ip_address)))))
           checked++;
        else
           return false;
        
        
        //all 4 conditions satisfied
        if(checked == 4)
            return true;
        
        return false;
    }
    
};




class Firewall
{
public:
    //vector of pointers to store all the rules.
    vector<Rule*> input;
    
    //Constructor
    Firewall(string input_path)
    {
        istringstream file(input_path);//changed to istringstream for easy testing. Can be replaces with ifstream for file input
        string line = "";
        
        while (getline(file, line))//iterating through each line in the file
        {
            Rule* to_push = new Rule(line);
            
            input.push_back(to_push);
        }
    }
    
    //Accept packet function
    bool accept_packet (string direction, string protocol, int port, string ip_address)
    {
        for(auto rule : this->input)
        {
            if(rule->is_match(direction, protocol, port, ip_address))
                return true;
        }
        
        return false;
    }
    
    
    
};


int main(int argc, const char * argv[])
{
    //Basic test case from the assignment
    Firewall testing("inbound,tcp,80,192.168.1.2\noutbound,tcp,10000-­20000,192.168.10.11\ninbound,udp,53,192.168.1.1-­192.168.2.5\noutbound,udp,1000-­2000,52.12.48.92");
    
    if( testing.accept_packet("inbound", "tcp", 80, "192.168.1.2"))//matches first rule
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
    if( testing.accept_packet("inbound", "udp", 53, "192.168.2.1"))//matches third rule
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
    if( testing.accept_packet("outbound", "tcp", 10234, "192.168.10.11"))//matches second rule
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    if( testing.accept_packet("inbound", "tcp", 81, "192.168.1.2"))//should return false
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    if( testing.accept_packet("inbound", "udp", 24, "52.12.48.92"))//should return false
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
    
    //Custom Test Cases
    
    //Did not test the validity of the input file as we can assume it is valid
    
    
    Firewall custom("inbound,tcp,80,192.168.1.2\noutbound,tcp,10000-­20000,192.168.1.1-­192.168.2.5\ninbound,udp,53,192.168.1.1-­192.168.2.5\noutbound,udp,1000-­2000,52.12.48.92");
    
    //end of range for both ip address and port
    if(custom.accept_packet("outbound", "tcp", 10000, "192.168.2.5"))//matches second case
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
    
    //This test case revealed an issue with my code
    //Handle IP addresses
    if(custom.accept_packet("outbound", "tcp", 10006, "192.168.1.256"))//matches secon case
    {
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
}
