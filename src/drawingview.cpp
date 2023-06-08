#include <wx/graphics.h>

#include <memory>

#include "drawingview.h"
#include "myapp.h"
#include "drawingcanvas.h"

#include "shapefactory.h"

wxIMPLEMENT_DYNAMIC_CLASS(DrawingView, wxView);

bool DrawingView::OnCreate(wxDocument *doc, long flags)
{
    if (!wxView::OnCreate(doc, flags))
    {
        return false;
    }

    MyApp::SetupCanvasForView(this);

    return true;
}

bool DrawingView::OnClose(bool deleteWindow)
{
    if (deleteWindow)
    {
        MyApp::SetupCanvasForView(nullptr);
    }
    return wxView::OnClose(deleteWindow);
}

void DrawingView::OnChangeFilename()
{
    wxString appName = wxTheApp->GetAppDisplayName();
    wxString title;

    wxString docName = GetDocument()->GetUserReadableName();
    title = docName + (GetDocument()->IsModified() ? " - Edited" : "") + wxString(_(" - ")) + appName;

    GetFrame()->SetLabel(title);
}

void DrawingView::OnDraw(wxDC *dc)
{
    dc->SetBackground(*wxWHITE_BRUSH);
    dc->Clear();

    std::unique_ptr<wxGraphicsContext> gc{wxGraphicsContext::CreateFromUnknownDC(*dc)};

    if (gc)
    {
        for (const auto &s : GetDocument()->shapes)
        {
            s->Draw(*gc);
        }
    }
}

void DrawingView::OnMouseDown(wxPoint pt)
{
    GetDocument()->shapes.push_back(ShapeFactory::Create(MyApp::GetToolSettings(), pt));
    GetDocument()->Modify(true);
}

void DrawingView::OnMouseDrag(wxPoint pt)
{
    GetDocument()->shapes.back()->HandleCreationByMouseDrag(pt);
    GetDocument()->Modify(true);
}

void DrawingView::OnMouseDragEnd()
{
    // Nothing to do here
}

void DrawingView::OnClear()
{
    GetDocument()->shapes.clear();
    GetDocument()->Modify(true);
}

DrawingDocument *DrawingView::GetDocument() const
{
    return wxStaticCast(wxView::GetDocument(), DrawingDocument);
}