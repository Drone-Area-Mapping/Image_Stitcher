#include "GAVS.h"

using namespace std;
using namespace cv;
using json = nlohmann::json;
json jsonRaw;

GAVS::GAVS()
{
    cout << "Initializing stitcher" << endl;
};

int GAVS::stitch()
{
    if (clusterCounter == 1)
    {
        final = true;
    }
    else
    {
        final = false;
    }
    setInputPath();
    setOutputPath();

    

    PlaySound(TEXT("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\Dreamscape.wav"), NULL, SND_ASYNC);

    cout << "Stitching images from path: " << inputPath.c_str() << endl;
    getAmountOfFiles();
    cout << "fileCounter: " << amountOfFiles << endl;
    cout << "clusterCounter: " << clusterCounter << endl;
    cout << "stitchCounter: " << stitchCounter << endl;
    //implement part to only stitch one cluster at a time
    while(stitchCounter < clusterCounter)
    {
        vector<Mat> imgs;
        for (int i = 0; i < clusterSize; i++)
        {
            if (clusters[stitchCounter][i] != NULL)
            {
                String file = to_string(clusters[stitchCounter][i]) + fileType;                                //note: remove the +1 here if file count starts at 0 instead of 1
                Mat img = imread(inputPath + file);
                cout << "Loaded image: " << file.c_str() << endl;
                if (img.empty())
                {
                    cout << "       Can't read image (probably incorrect naming of file)\n ";
                    cout << "       file: " << inputPath + file << "\n";
                    return -1;
                }
                imgs.push_back(img);                                                  //load images
            }
            else
            {
                cout << "Received empty field in cluster array?\n ";
            }
        }
        Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::SCANS);
        Stitcher::Status status = stitcher->stitch(imgs, scan);

        if (status != Stitcher::OK)
        {
            cout << "Can't stitch images\n";
            return -1;
        }
        imwrite(outputPath + to_string(stitchCounter + 1) + fileType, backgroundRemover(scan));            //save the stitched file
        cout << "Stitch saved: " << outputPath + to_string(stitchCounter + 1) + fileType << endl;
        stitchCounter++;
        totalStitchCounter++;
        updateProgress();
        if (getSocketLine() == "stopProcessing")
        {
            stitchCounter = 301;
        }
    }
    fullCycleItterator++;
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

Mat GAVS::backgroundRemover(Mat input)
{
    Mat output;
    cvtColor(input, output, COLOR_BGR2BGRA);
    for (int y = 0; y < output.rows; ++y)
    {
        for (int x = 0; x < output.cols; ++x)
        {
            Vec4b& pixel = output.at<Vec4b>(y, x);
            if (pixel[0] <= backgroundBlackLevel && pixel[1] <= backgroundBlackLevel && pixel[2] <= backgroundBlackLevel)
            {
                pixel[3] = 0;
            }
        }
    }
    return output;
};

void GAVS::clearClusters()
{
    cout << "resetting GAVS clusters\n";
    clusterCounter = 0;
    stitchCounter = 0;
}

void GAVS::updateProgress()
{
    json progressJson;
    progressJson["name"] = "stitchProgress";
    progressJson["value"] = (100/totalAmountOfActions) * totalStitchCounter;
    cout << "stitchCounter: " << totalStitchCounter << "\namountOfActions: " << totalAmountOfActions << "\n";
    socket.write_line(progressJson.dump());
    cout << "set progress to: " << to_string((100 / totalAmountOfActions) * totalStitchCounter).c_str() << "% \n";
}

void GAVS::setInputBasePath(String input)
{
    totalStitchCounter = 0;
    inputBasePath = input+"\\";
    cout << "Input path set to: " << inputBasePath.c_str() << "\n";
};

void GAVS::setOutputBasePath(String output)
{
    outputBasePath = output + "\\";
    cout << "Output path set to: " << outputBasePath.c_str() << "\n";
};

void GAVS::setInputPath()                     //stitching programs current input path is defined by the fullCycleItterator and basepath
{
    if (fullCycleItterator == 0)
    {
        inputPath = inputBasePath;
    }
    else
    {
        inputPath = outputBasePath + tempFiles + to_string(fullCycleItterator) + "\\";
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
        executeWinCommand(String("cd /d " + outputBasePath + " & mkdir " + outputPath).c_str());
        outputPath = outputBasePath + outputPath + "\\";
    }
};

bool GAVS::setCluster(vector<int> inputClusters)
{
    //perhaps change NULL receiving cluster input to -1?
    if (inputClusters.size() == 0)
    {
        cout << "incorrect cluster input\n";
        return false;
    }
    for (int i = 0; i < inputClusters.size(); i++)
    {
        clusters[clusterCounter][i] = inputClusters.at(i);
    }
    cout << "[";
    for(int i = 0; i < 4; i++) cout << clusters[clusterCounter][i] << ", ";
    cout << "]" << endl;
    clusterCounter++;
    return true;
};

void GAVS::setProgressInfo(SocketSlave socketInput, int amountOfActions)
{
    socket = socketInput;
    totalAmountOfActions = amountOfActions - 1;
};

String GAVS::getSocketLine()
{
    readBuffer = socket.returnline();
    if (readBuffer != "")
    {
        jsonRaw = json::parse(readBuffer);
        return jsonRaw["name"];
    }
    return "";
};

int GAVS::getAmountOfFiles()
{
    stringstream numOfFiles(executeWinCommand(String("cd " + inputPath + " & powershell \"Get-ChildItem | Measure-Object | %{$_.Count}\"").c_str()));
    numOfFiles >> amountOfFiles;
    return amountOfFiles;
};

bool GAVS::getFinal()
{
    if (fullCycleItterator >= maxItterationSafetyLimit) return true;        //prevent more than 10 full cycle itterations (equal to 1048576 images, should never be possible in any way whatsoever)
    return final;
}

