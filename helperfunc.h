#pragma once

#include <wx/wxprec.h>
#include <wx/listctrl.h>
#include <sys/uio.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <fstream>
#include <experimental/filesystem>
#include <string>
#include <dirent.h>
#include <stdlib.h>

namespace filesystem = std::experimental::filesystem;

struct info
{
        std::vector<std::string> names;
        std::vector<std::string> pid;
};

std::string pid = "";

struct info getProcNames(std::string pname)
{
    info info1;
    for ( filesystem::path p : filesystem::directory_iterator("/proc") )
    {
        std::string path = p.string();
        std::string pid = path.substr(6,std::string::npos);
        std::string pathtocheck = "/proc/" + pid + "/root";
        DIR *dir = opendir(pathtocheck.c_str());
        if(dir == NULL)
        {
            continue;
        }
        
        std::ifstream filee(path + "/status");
        std::string dataline;
        if(filee.good())
        {
            getline(filee, dataline);
            std::string name = dataline.substr(6, std::string::npos);
            if(name.find("main") != std::string::npos)
                continue;
            info1.names.push_back(name);
            info1.pid.push_back(pid);
        }
    }
    return info1;
}

void openProc( std::vector<long long> array, wxListCtrl *listctrl, int valuetosearch)
{
    wxListItem item1;
    struct iovec local[1];
    struct iovec remote[1];
    int *buf;
    buf = (int *) malloc(4);
    ssize_t readc;

    local[0].iov_base = (void *) buf;
    local[0].iov_len = 4;
    //remote[0].iov_base = (void *) array[0];
    remote[0].iov_len = 4;
    
    int counter = 0;
    for(long long i = array[0]; i < array[1] ; i+= 4 )
    {
        remote[0].iov_base = (void *) i;
        readc = process_vm_readv(std::stoi(pid), local, 1, remote, 1, 0);
        if (readc != 4)
        {
            wxMessageBox("Error: Please Restart App as Root", "Info", wxOK | wxICON_INFORMATION);
            free(buf);
            break;
        }
        else if(*buf == valuetosearch)
        {
            item1.SetId(counter);
            item1.SetText("1");
            listctrl->InsertItem(item1);
            listctrl->SetItem(counter, 1, std::to_string(*buf));
            std::stringstream stream;
            stream << std::hex << i;
            std::string result( "0x" + stream.str() );
            listctrl->SetItem(counter, 0, result);
            counter += 1;
        }
        
    }
    free(buf);
}

std::vector<long long> getAddresses()
{
    std::vector<long long> array;
    if(pid == "")
    {
        wxMessageBox( "Please Open A Process First!", "Info" , wxOK | wxICON_INFORMATION );
        return array;
    }
    std::ifstream file("/proc/" + pid + "/maps");
    if(file.good())
    {
        std::string line;
        while(std::getline(file, line))
        {
            if(line.find("stack") != std::string::npos)
            {
                short int index1 = line.find("-");
                short int index2 = line.find(" ");
                if( (index1 == std::string::npos) || (index2 == std::string::npos) )
                {
                    wxMessageBox( "Unable to scan process", "Info" , wxOK | wxICON_INFORMATION );
                    return array;
                }
                std::string add1 = line.substr(0, index1);
                std::string add2 = line.substr(index1+1, index2-index1);
                array.push_back( ((long long)strtol(add1.c_str(), NULL, 16) ));
                array.push_back( ((long long)strtol(add2.c_str(), NULL, 16) ));
                return array;
            }
        }
    }
}

bool WriteMem(std::string addr, int value)
{
    long long address = ((long long) strtol(addr.c_str(), NULL, 16));
    struct iovec local[1];
    struct iovec remote[1];
    int val = value;
    local[0].iov_base = (void *) &val;
    local[0].iov_len = 4;
    remote[0].iov_base = (void *) address;
    remote[0].iov_len = 4;
    ssize_t nread;
    nread = process_vm_writev( std::stoi(pid), local, 1, remote, 1, 0);
    if(nread != 4)
    {
        wxMessageBox( "Unable to write to process", "Info" , wxOK | wxICON_INFORMATION );
        return false;
    }
    return true;
}