#include <opencv2/opencv.hpp>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>

int main()
{
    std::cout << "Starte GestureNoticer...\n";
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // Test 1: simples Bildfenster
    cv::Mat test(240, 320, CV_8UC3, cv::Scalar(40, 40, 40));
    cv::putText(test, "OpenCV OK!", {20, 120}, cv::FONT_HERSHEY_SIMPLEX, 0.8, {200, 200, 200}, 2);
    cv::imshow("Testfenster (5s)", test);
    cv::waitKey(500); // kurz zeigen, danach Webcam versuchen

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

    // JSON laden
    std::ifstream file("assets/memes.json");
    if (!file.is_open())
    {
        std::cerr << "Konnte memes.json nicht oeffnen!\n";
        return 1;
    }

    // In ein JSON-Objekt parsen
    nlohmann::json memes;
    file >> memes;

    // Zugriffstest
    if (memes.contains("fist_up"))
    {
        std::string path = memes["fist_up"];
        std::cout << "Pfad zum Meme: " << path << "\n";

        // Testweise Bild laden und anzeigen
        cv::Mat meme = cv::imread(path);
        if (!meme.empty())
        {
            cv::imshow("Meme-Test", meme);
            cv::waitKey(2000); // 2s anzeigen
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

    while (true)
    {
        cv::Mat frame;
        cam >> frame;
        if (frame.empty())
        {
            std::cerr << "Leerer Frame – breche ab.\n";
            break;
        }
        cv::imshow("Webcamarsch", frame);

        // ESC beendet
        if (cv::waitKey(1) == 27)
            break;
    }
    std::cout << "Programm Ende.\n";
    return 0;
}
