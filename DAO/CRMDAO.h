#pragma once
#include <string_view>

using namespace std;

namespace crm {
const static int ID_TABLE_INDEX{0};
const static int NAME_TABLE_INDEX{1};
const static int EMAIL_TABLE_INDEX{2};
const static int SUBSCRIBED_TABLE_INDEX{3};
constexpr string_view DATA_FILE{"resources/crm.csv"};
static vector<string_view> headers = {"Id", "Name", "Email", "Subscribed"};

class CRMDAO {
};

}