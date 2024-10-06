#include "../../third_party/argparse/argparse.h"

void sift_test1B();
void sift_test1B_fp();
int main(int argc, char *argv[]) {
    argparse::ArgumentParser parser("sift_1b");

    parser.add_argument("-f", "--float")
    .help("run sift 1b as float point interface")
    .default_value(false)
    .implicit_value(true);

    parser.parse_args(argc, argv);

    if (parser["--float"] == true) {
        sift_test1B_fp();
    } else {
        sift_test1B();
    }
    return 0;
}
