#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;
//using namespace std;

typedef enum EPointFrom     {PREV_FRAME=0,  NEXT_FRAME=1};
typedef enum EPeinterState  {SM_END=0,      SM_START=1};

EPointFrom      actualMode_e = PREV_FRAME;
EPeinterState   actualPainterState_e = SM_END;

struct mouse_info_struct {  int x,y; };
struct mouse_info_struct mouse_Start, mouse_End;

typedef struct CPainterLine {
     Point startPoint;
     Point endPoint;
     };

class CStringContainer
{
    public:

        typedef enum EReprOrigo {O_TOPLEFT=0, O_BOTTOMLEFT=1, O_TOPRIGHT=2, O_BOTTOMRIGHT=3};

        /// C'tor
        CStringContainer(int f_width_i32, int f_height_i32, EReprOrigo f_origo_e):
            m_reprWidth_i32(f_width_i32),
            m_reprHeight_i32(f_height_i32)
        {
            m_origoHorizOffset_i32  = 0;
            m_origoVertOffset_i32   = 0;
            /// @TODO: Masking is easier
            switch(f_origo_e)
            {
                case O_TOPLEFT:
                    break;
                case O_BOTTOMLEFT:
                    m_origoVertOffset_i32 = f_height_i32;
                    break;
                case O_TOPRIGHT:
                    m_origoHorizOffset_i32 = f_width_i32;
                    break;
                case O_BOTTOMRIGHT:
                    m_origoVertOffset_i32 = f_height_i32;
                    m_origoHorizOffset_i32 = f_width_i32;
                    break;
                default:
                    break;
            }
        }

        void addToContainer_vd(const EPointFrom f_pointFrame_e, const CPainterLine& f_canvasLine_r, const int& f_canvasWidth_i32, const int& f_canvasHeight_i32)
        {
            CPainterLine l_newLine;
            float l_wFactor_f32 = (static_cast<float>(m_reprWidth_i32) / static_cast<float>(f_canvasWidth_i32));
            float l_hFactor_f32 = (static_cast<float>(m_reprHeight_i32) / static_cast<float>(f_canvasHeight_i32));
            int l_wReprStartX_i32 = m_origoHorizOffset_i32 - static_cast<int>( f_canvasLine_r.startPoint.x * l_wFactor_f32);
            int l_wReprStartY_i32 = m_origoVertOffset_i32  - static_cast<int>( f_canvasLine_r.startPoint.y* l_hFactor_f32);
            int l_wReprEndX_i32 = m_origoHorizOffset_i32 - static_cast<int>( f_canvasLine_r.endPoint.x* l_wFactor_f32);
            int l_wReprEndY_i32 = m_origoVertOffset_i32  - static_cast<int>( f_canvasLine_r.endPoint.y* l_hFactor_f32);
            l_newLine.startPoint = cv::Point( l_wReprStartX_i32, l_wReprStartY_i32);
            l_newLine.endPoint   = cv::Point( l_wReprEndX_i32, l_wReprEndY_i32);


            if(PREV_FRAME == f_pointFrame_e)
            {
                m_prevLineVect_v.push_back(l_newLine);
            }
            else if(NEXT_FRAME == f_pointFrame_e)
            {
                m_nextLineVect_v.push_back(l_newLine);
            }
        }


        void removeLastFromContainer(const EPointFrom f_pointFrame_e)
        {
            if(PREV_FRAME == f_pointFrame_e && false == m_prevLineVect_v.empty())
            {
                m_prevLineVect_v.pop_back();
            }
            else if(NEXT_FRAME == f_pointFrame_e && false == m_nextLineVect_v.empty())
            {
                m_nextLineVect_v.pop_back();
            }
        }

        bool empty(const EPointFrom f_pointFrame_e)
        {
            if(PREV_FRAME == f_pointFrame_e )
            {
                return m_prevLineVect_v.empty();
            }
            else if(NEXT_FRAME == f_pointFrame_e)
            {
                return m_nextLineVect_v.empty();
            }
        }

        void getLineBuffer(const EPointFrom f_pointFrame_e, vector<CPainterLine>& f_canvasLines_rv, const int& f_canvasWidth_i32, const int& f_canvasHeight_i32)
        {
            /// Reset the output buffer
            f_canvasLines_rv.resize(0);

            vector<CPainterLine>* selectedBuffer_rf;
            if(PREV_FRAME == f_pointFrame_e)
            {
                selectedBuffer_rf = &m_prevLineVect_v;
            }
            else
            {
                selectedBuffer_rf = &m_nextLineVect_v;
            }
            for(int idx_i32=0; idx_i32<selectedBuffer_rf->size(); ++idx_i32)
            {
                CPainterLine l_reprLine = selectedBuffer_rf->at(idx_i32);
                CPainterLine l_canvasLine;
                float l_wFactor_f32 = (static_cast<float>(f_canvasWidth_i32) / static_cast<float>(m_reprWidth_i32));
                float l_hFactor_f32 = (static_cast<float>(f_canvasHeight_i32) / static_cast<float>(m_reprHeight_i32));
                int l_wCanvStartX_i32 = static_cast<int>( (m_origoHorizOffset_i32 - l_reprLine.startPoint.x)* l_wFactor_f32);
                int l_wCanvStartY_i32 = static_cast<int>( (m_origoVertOffset_i32  - l_reprLine.startPoint.y)* l_hFactor_f32);
                int l_wCanvEndX_i32 = static_cast<int>( (m_origoHorizOffset_i32 - l_reprLine.endPoint.x)* l_wFactor_f32);
                int l_wCanvEndY_i32 = static_cast<int>( (m_origoVertOffset_i32  - l_reprLine.endPoint.y)* l_hFactor_f32);
                l_canvasLine.startPoint = cv::Point( l_wCanvStartX_i32, l_wCanvStartY_i32);
                l_canvasLine.endPoint   = cv::Point( l_wCanvEndX_i32, l_wCanvEndY_i32);

                f_canvasLines_rv.push_back(l_canvasLine);
            }

        }

        void saveStrings(string f_filename_s)
        {
            std::ofstream l_stringFile;
            l_stringFile.open (f_filename_s);
            //l_stringFile << "Writing this to a file.\n";
            l_stringFile << std::endl << "struct CDrawedStrings { int m_horStart_i32; int m_verStart_i32; int m_horEnd_i32; int m_verEnd_i32;};" << std::endl << std::endl;

            l_stringFile << "CDrawedStrings l_vectPrev["<< m_prevLineVect_v.size() << "] = {" << std::endl << "// PREV" << std::endl;
            for(int idx_i32=0; idx_i32<m_prevLineVect_v.size(); ++idx_i32)
            {
                CPainterLine l_reprLine = m_prevLineVect_v.at(idx_i32);
                l_stringFile << " { " << l_reprLine.startPoint.x << " , " << l_reprLine.startPoint.y << "    , " <<
                                         l_reprLine.endPoint.x << " , " << l_reprLine.endPoint.y << " }";

                if(idx_i32 < m_prevLineVect_v.size()-1)
                {
                    l_stringFile << ",";
                }

                l_stringFile << std::endl;
            }

            l_stringFile << "};";

            l_stringFile << std::endl << std::endl << std::endl;

            l_stringFile << "CDrawedStrings l_vectNext["<< m_nextLineVect_v.size() << "] = {" << std::endl << "// NEXT" << std::endl;
            for(int idx_i32=0; idx_i32<m_nextLineVect_v.size(); ++idx_i32)
            {
                CPainterLine l_reprLine = m_nextLineVect_v.at(idx_i32);
                l_stringFile << " { " << l_reprLine.startPoint.x << " , " << l_reprLine.startPoint.y << "    , " <<
                                         l_reprLine.endPoint.x << " , " << l_reprLine.endPoint.y << " }";

                if(idx_i32 < m_nextLineVect_v.size()-1)
                {
                    l_stringFile << ",";
                }

                l_stringFile << std::endl;
            }
            l_stringFile << "};" << std::endl;
            l_stringFile.close();
        }

    private:
        const int m_reprWidth_i32;    ///< Width of string representation
        const int m_reprHeight_i32;   ///< Height of string representation
        int m_origoHorizOffset_i32;   ///< Offset the horizontal origo
        int m_origoVertOffset_i32;    ///< Offset the horizontal origo

        vector<CPainterLine> m_prevLineVect_v;   ///< Line buffer for previous frame
        vector<CPainterLine> m_nextLineVect_v;  ///< Line buffer for next frame
};


CStringContainer g_stringContainer(1800,1800, CStringContainer::EReprOrigo::O_BOTTOMRIGHT);
Mat canvasImage(600, 600, CV_8UC3);


void on_mouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		mouse_Start.x = x;
		mouse_Start.y = y;

		actualPainterState_e = SM_START;
	}
	else if (event == CV_EVENT_LBUTTONUP)
    {
        mouse_End.x = x;
		mouse_End.y = y;

		actualPainterState_e = SM_END;

        CPainterLine newLine;
        newLine.startPoint = Point(mouse_Start.x, mouse_Start.y);
        newLine.endPoint = Point(mouse_End.x, mouse_End.y );

        g_stringContainer.addToContainer_vd(actualMode_e, newLine, canvasImage.size().width, canvasImage.size().height);
    }
    else
    {
        mouse_End.x = x;
		mouse_End.y = y;
    }
}

void DrawText_vd(Mat& f_img_r )
{
    string l_text_str;
    if(PREV_FRAME == actualMode_e) { l_text_str = "PrevFrame";  }
    else{ l_text_str = "NextFrame";}

    putText(f_img_r, l_text_str, Point(10,20), FONT_HERSHEY_PLAIN, 1.0,  Scalar::all(255), 1, 8);

    string l_textUsage_str = "[M] toggle mode    [S] save strings    [B] remove last string";
    putText(f_img_r, l_textUsage_str, Point(10,590), FONT_HERSHEY_PLAIN, 0.7,  Scalar::all(255), 1, 8);
}



int main (int argc, char * const argv[])
{

	namedWindow("StringPainter");
	setMouseCallback("StringPainter", on_mouse, 0);
	char code = (char)-1;

    for(;;)
    {
        // Clear canvas
        canvasImage = Scalar::all(0);

        // draw previous lines
        vector<CPainterLine> tempBuffer;
        g_stringContainer.getLineBuffer(PREV_FRAME, tempBuffer, canvasImage.size().width, canvasImage.size().height);
        for(int idxPrev=0; idxPrev < tempBuffer.size(); ++idxPrev )
        {
            CPainterLine storedLine = tempBuffer.at(idxPrev);
            line(canvasImage, storedLine.startPoint, storedLine.endPoint, Scalar(0,255,0), 2);
        }

        // draw previous lines
        g_stringContainer.getLineBuffer(NEXT_FRAME, tempBuffer, canvasImage.size().width, canvasImage.size().height);
        for(int idxNext=0; idxNext < tempBuffer.size(); ++idxNext )
        {
            CPainterLine storedLine = tempBuffer.at(idxNext);
            line(canvasImage, storedLine.startPoint, storedLine.endPoint, Scalar(255,0,0), 2);
        }

        // Print actual
        if(SM_START == actualPainterState_e)
        {
            if(PREV_FRAME==actualMode_e)
            {
                line(canvasImage, Point(mouse_Start.x,mouse_Start.y), Point(mouse_End.x, mouse_End.y), Scalar(0,200,0), 1);
            }
            if(NEXT_FRAME==actualMode_e)
            {
                line(canvasImage, Point(mouse_Start.x,mouse_Start.y), Point(mouse_End.x, mouse_End.y), Scalar(200,0,0), 1);
            }

        }

        DrawText_vd(canvasImage);
        imshow( "StringPainter", canvasImage );
        code = (char)waitKey(60);

        //std::cout << "code:"<< static_cast<int>(code) << std::endl;

        // Toggle paint mode
        if (109 == code) // M
        {
            if (PREV_FRAME == actualMode_e) { actualMode_e = NEXT_FRAME; }
            else if (NEXT_FRAME == actualMode_e) { actualMode_e = PREV_FRAME; }
            else{;}
        }

        // Save the painted strings
        if (115 == code) // S
        {
            g_stringContainer.saveStrings("something.txt");
            imwrite( "actStrings.jpg", canvasImage );

        }

        // Remove the last string in actual mode
        if (98 == code) // B
        {
            g_stringContainer.removeLastFromContainer(actualMode_e);
        }

        // Exit
        if( code == 27 ) // ESC
            break;
    }

    return 0;
}
