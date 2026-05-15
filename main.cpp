#include <opencv2/opencv.hpp>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>

int main()
{
    std::cout << "Starte GestureNoticer...\n";
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // Test 1: simples window
    cv::Mat test(240, 320, CV_8UC3, cv::Scalar(40, 40, 40));
    cv::putText(test, "OpenCV OK!", {20, 120}, cv::FONT_HERSHEY_SIMPLEX, 0.8, {200, 200, 200}, 2);
    cv::imshow("Testfenster (5s)", test);
    cv::waitKey(500);

    // Test 2: Webcam
    std::cout << "Oeffne Kamera..." << std::endl;
    cv::VideoCapture cam;
    int selectedBackend = -1;
    int selectedIndex = -1;
    const std::vector<int> backends = {cv::CAP_DSHOW, cv::CAP_MSMF};
    for (int backend : backends)
    {
        for (int index = 0; index <= 3; ++index)
        {
            if (cam.open(index, backend))
            {
                selectedBackend = backend;
                selectedIndex = index;
                break;
            }
        }
        if (cam.isOpened())
            break;
    }
    if (!cam.isOpened())
    {
        std::cerr << "KAMERA NICHT GEFUNDEN (Backend DSHOW/MSMF, Index 0..3). Druecke Enter zum Beenden.\n";
        std::cin.get();
        return 1;
    }
    std::cout << "Kamera-Backend: " << selectedBackend << ", Index: " << selectedIndex << "\n";

    std::cout << "Kamera offen. ESC zum Beenden.\n";

    // loads JSON
    std::ifstream file("assets/memes.json");
    if (!file.is_open())
    {
        std::cerr << "Konnte memes.json nicht oeffnen!\n";
        return 1;
    }

    // parse into JSON object
    nlohmann::json memes;
    file >> memes;

    if (memes.contains("fist_up"))
    {
        std::string path = memes["fist_up"];
        std::cout << "Pfad zum Meme: " << path << "\n";

        // test for a pic
        cv::Mat meme = cv::imread(path);
        if (!meme.empty())
        {
            cv::imshow("Meme-Test", meme);
            cv::waitKey(2000);
        }
        else
        {
            std::cerr << "Konnte Bild '" << path << "' nicht laden!\n";
        }
    }
    else
    {
        std::cerr << "Key 'fist_up' fehlt in meme.json!\n";
    }
    auto lastTick = cv::getTickCount();
    while (true)
    {
        cv::Mat frame;
        cam >> frame;
        if (frame.empty())
        {
            std::cerr << "Leerer Frame – breche ab.\n";
            break;
        }

        auto nowTick = cv::getTickCount();
        double dt = (nowTick - lastTick) / cv::getTickFrequency();
        lastTick = nowTick;
        double fps = (dt > 0.0) ? (1.0 / dt) : 0.0;

        std::string overlay = "FPS: " + std::to_string(static_cast<int>(fps));
        cv::putText(frame, overlay, {20, 40}, cv::FONT_HERSHEY_SIMPLEX, 1.0, {0, 255, 0}, 2);
        cv::imshow("Webcamarsch", frame);

        // ESC for close
        if (cv::waitKey(1) == 27)
            break;
    }
    std::cout << "Programm Ende.\n";
    return 0;
}
