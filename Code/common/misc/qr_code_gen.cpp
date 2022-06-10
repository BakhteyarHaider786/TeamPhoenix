#include "../../lib/qr/qrcodegen.hpp"
#include "qr_code_gen.h"

#include <fstream>
#include <string>

using namespace qrcodegen;

using std::string;
using std::stringstream;
using std::ofstream;

string QrCodeGen::saveToFile(entry_t entry) {
    stringstream stream;
    ofstream qr_file;
    string path = string("qr/") + entry.area + "_" + entry.category + "-" + entry.number + ".svg";

    stream << entry.nid << " : " << entry.area << "-" << entry.category << "-" << entry.number;

    QrCode qr =  QrCode::encodeText(stream.str().c_str(), QrCode::Ecc::LOW);

    int border = 4;
    qr_file.open(path);
    qr_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    qr_file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    qr_file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    qr_file << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    qr_file << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    qr_file << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    qr_file << " ";
                qr_file << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    qr_file << "\" fill=\"#000000\"/>\n";
    qr_file << "</svg>\n";

    qr_file.flush();
    qr_file.close();

    return path;
}
