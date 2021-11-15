#include "GAVS.h"

GAVS::GAVS()
{
    cout << "Initializing stitcher" << endl;
};



int GAVS::stitch()
{
    
    setInputPath();
    setOutputPath();

    cout << "Stitching images from path: " << inputPath.c_str() << endl;
    getAmountOfFiles();
    cout << "fileCounter: " << amountOfFiles << endl;

    for (int i = 1; i < amountOfFiles; ++i)
    {
        String file = to_string(i + 1) + fileType;                                //note: remove the +1 here if file count starts at 0 instead of 1
        Mat img = imread(inputPath + file);
        if (img.empty())
        {
            cout << "Can't read image (probably incorrect naming of file)\n ";
            return -1;
        }
        imgs.push_back(img);                                                    //load images
    }

    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::SCANS);
    Stitcher::Status status = stitcher->stitch(imgs, scan);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        return -1;
    }
    imwrite(outputPath + to_string(stitchCounter) + fileType, scan);            //save the stitched file
    cout << "Stitch saved: " << outputPath + to_string(stitchCounter) + fileType << endl;
};

string GAVS::executeWinCommand(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
};

void GAVS::setInputBasePath(String input)
{
    inputBasePath = input;
};

void GAVS::setOutputBasePath(String output)
{
    outputBasePath = output;
};

void GAVS::setInputPath()                     //stitching programs current input path is defined by the fullCycleItterator and basepath
{
    if (fullCycleItterator == 0)
    {
        inputPath = inputBasePath;
    }
    else
    {
        inputPath = tempFiles + to_string(fullCycleItterator);
    }
};

void GAVS::setOutputPath()
{
    if (final)
    {
        outputPath = outputBasePath;
    }
    else
    {
        outputPath = tempFiles + to_string(fullCycleItterator + 1);
        executeWinCommand(String("cd /d "+outputBasePath + " & mkdir "+outputPath).c_str());
        outputPath = outputBasePath + outputPath + "\\";
    }
    
}

int GAVS::getAmountOfFiles()
{
    stringstream numOfFiles(executeWinCommand(String("cd " + inputPath + " & powershell \"Get-ChildItem | Measure-Object | %{$_.Count}\"").c_str()));
    numOfFiles >> amountOfFiles;
    return amountOfFiles;
}

