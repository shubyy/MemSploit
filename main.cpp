#include "init.h"
#include "helperfunc.h"

namespace filesystem = std::experimental::filesystem;

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    Frame *frame = new Frame("MemSploit", wxPoint(50,50), wxSize(570, 600));
    frame->Show(true);
    return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    menuFile->Append(ID_Hello, "&Refresh...\tCtrl-H", "Scan PC for running Processes");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuHelp->Append(wxID_ABOUT);
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );

    wxListItem col0;
    col0.SetId(0);
    col0.SetText( "Process Name");
    col0.SetWidth(170);
    col0.SetAlign(wxLIST_FORMAT_LEFT);
    listctrl1->InsertColumn(0, col0);
    col0.SetId(1);
    col0.SetText("PID");
    col0.SetWidth(50);
    col0.SetAlign(wxLIST_FORMAT_LEFT);
    listctrl1->InsertColumn(1, col0);

    col0.SetId(0);
    col0.SetText( "Address");
    col0.SetWidth(180);
    col0.SetAlign(wxLIST_FORMAT_LEFT);
    listctrl2->InsertColumn(0, col0);
    col0.SetId(1);
    col0.SetText("Value");
    col0.SetWidth(100);
    col0.SetAlign(wxLIST_FORMAT_CENTER);
    listctrl2->InsertColumn(1, col0);

    col0.SetId(0);
    col0.SetText( "Address");
    col0.SetWidth(150);
    col0.SetAlign(wxLIST_FORMAT_LEFT);
    listctrl3->InsertColumn(0, col0);
    col0.SetId(1);
    col0.SetText("Value");
    col0.SetWidth(130);
    col0.SetAlign(wxLIST_FORMAT_CENTER);
    listctrl3->InsertColumn(1, col0);

    wxCommandEvent e;
    OnHello(e);
}

void Frame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void Frame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "idk", "Info",wxOK | wxICON_INFORMATION );
}

void Frame::OnHello(wxCommandEvent& event)
{
    listctrl1->DeleteAllItems();
    wxString par2(wxGetApp().argv[0]);
    info info1 = getProcNames(par2.ToStdString());

    wxListItem item1;
    for(int i = 0; i < info1.names.size(); i++)
    {
        item1.SetId(i);
        item1.SetText("1");
        listctrl1->InsertItem(item1);
        listctrl1->SetItem(i, 1, info1.pid[i]);
        listctrl1->SetItem(i, 0, info1.names[i]);
    }
}

void Frame::Button2Clicked(wxCommandEvent& event)
{
    int valuetosearch;
    std::string value = textctrl1->GetLineText(0).ToStdString();
    try {
        valuetosearch = std::stoi(value);
    }
    catch (const std::exception& e)
    {
        wxMessageBox( "Error: Please Enter A int value", "Info" , wxOK | wxICON_INFORMATION );
        return;
    }
    listctrl2->DeleteAllItems();
    std::vector<long long> addresses = getAddresses();
    if (addresses.size() == 0)
        return;

    openProc( addresses, listctrl2, valuetosearch);
}

void Frame::Button1Clicked(wxCommandEvent& e)
{
    int itemindex = 0;
    bool found = false;
    while ((itemindex = listctrl1->GetNextItem(itemindex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND )
    {
        found = true;
        break;
    }
    if(found == false)
    {
        wxMessageBox( "No Process Selected!", "Info" , wxOK | wxICON_INFORMATION );
        return;
    }
    pid = (listctrl1->GetItemText(itemindex, 1)).ToStdString();
    text1->SetLabel("Current Process Open: " + listctrl1->GetItemText(itemindex, 0) );
}

void Frame::List2Clicked(wxListEvent& event)
{
    int itemindex = -1;
    wxListItem item1;
    int counter = 0;
    while ((itemindex = listctrl2->GetNextItem(itemindex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND )
    {
        item1.SetId(counter);
        item1.SetText("1");
        listctrl3->InsertItem(item1);
        listctrl3->SetItem(counter, 0, listctrl2->GetItemText(itemindex, 0));
        listctrl3->SetItem(counter, 1, listctrl2->GetItemText(itemindex, 1));
        counter += 1;
    }
}

void Frame::Button3Clicked(wxCommandEvent& event)
{
    int itemindex;
    for(itemindex = 0; itemindex < listctrl3->GetItemCount(); itemindex++ )
    {
        int value;
        try {
            value = std::stoi( textctrl2->GetLineText(0).ToStdString() );
        }
        catch (const std::exception& e) {
            wxMessageBox( "Error: Please Enter A int value", "Info" , wxOK | wxICON_INFORMATION );
            return;
        }
        bool wrote = WriteMem(listctrl3->GetItemText(itemindex, 0).ToStdString(), value);
        if(wrote == false)
        {
            return;
        }
        wxString newvalue;
        newvalue << value;
        listctrl3->SetItem(itemindex, 1, newvalue);
    }
}



