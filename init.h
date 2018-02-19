#pragma once
#include <wx/wxprec.h>
#include <wx/listctrl.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class App : public wxApp
{
public:
    virtual bool OnInit();
};

enum 
{
    ID_Hello,
    LISTID1,
    LISTID3,
    BUTTON1,
    BUTTON2,
    BUTTON3,
    BUTTON4,
    LISTID2,
    TEXTCTRL2,
    DIALOG1
};


class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& point, const wxSize& size);
    
private:
    //items
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(570, 600));
    wxListCtrl *listctrl1 = new wxListCtrl(panel, LISTID1, wxPoint(10,35), wxSize(240,200), wxLC_REPORT);
    wxListCtrl *listctrl2 = new wxListCtrl(panel, LISTID2, wxPoint(260,35), wxSize(300,200), wxLC_REPORT);
    wxListCtrl *listctrl3 = new wxListCtrl(panel, LISTID3, wxPoint(260,285), wxSize(300,200), wxLC_REPORT);
    wxButton *Button1 = new wxButton(panel, BUTTON1, "Open", wxPoint(10,245), wxSize(90, 30), wxBU_EXACTFIT);
    wxStaticText *text1 = new wxStaticText(panel, wxID_ANY, "Process List", wxPoint(15,10),wxSize(90, 20), wxALIGN_LEFT);
    wxStaticText *text3 = new wxStaticText(panel, wxID_ANY, "Memory List", wxPoint(350,10),wxSize(90, 20), wxALIGN_LEFT);
    wxTextCtrl *textctrl1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(360, 244), wxSize(100, 30), wxTE_CENTER);
    wxTextCtrl *textctrl2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(360, 500), wxSize(100, 27), wxTE_CENTER);
    wxButton *Button2 = new wxButton(panel, BUTTON2, "Search", wxPoint(470,245), wxSize(90, 27), wxBU_EXACTFIT);
    wxButton *Button3 = new wxButton(panel, BUTTON3, "Change", wxPoint(470,500), wxSize(90, 27), wxBU_EXACTFIT);
    //wxGauge *gauge1 = new wxGauge(panel, wxID_ANY, 350, wxPoint(110, 245), wxSize(350, 30), wxGA_HORIZONTAL);
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menuHelp = new wxMenu;
    wxMenu *menuFile = new wxMenu;
    //functions
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void Button1Clicked(wxCommandEvent& event);
    void Button2Clicked(wxCommandEvent& event);
    void Button3Clicked(wxCommandEvent& event);
    void List2Clicked(wxListEvent& event);

    wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(ID_Hello, Frame::OnHello)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
    EVT_BUTTON(BUTTON1, Frame::Button1Clicked)
    EVT_LIST_ITEM_ACTIVATED(LISTID2, Frame::List2Clicked)
    EVT_BUTTON(BUTTON2, Frame::Button2Clicked)
    EVT_BUTTON(BUTTON3, Frame::Button3Clicked)
wxEND_EVENT_TABLE()
