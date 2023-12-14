#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include<map>
#pragma warning(disable : 4996)
using namespace std;

// 设备信息结构体
struct EquipmentInfo {
    char equipCode[10];  // 设备编号
    char equipType[20];  // 设备种类
    char equipName[20];  // 设备名称
    float equipPrice;    // 设备价格
    char buyDate[20];    // 设备购入日期
    int scrap;           // 是否报废
    char scrapDate[20];  // 报废日期
};

// 函数声明
void inputEquipmentInfo(std::vector<EquipmentInfo>& equipments);
void addEquipment(vector<EquipmentInfo>& equipments);
void modifyEquipment(vector<EquipmentInfo>& equipments);
void saveToFile(const vector<EquipmentInfo>& equipments);
void loadFromFile(vector<EquipmentInfo>& equipments);
void searchEquipment(const vector<EquipmentInfo>& equipments);
void classifyEquipment(const vector<EquipmentInfo>& equipments);
void deleteEquipment(vector<EquipmentInfo>& equipments);
void printEquipment(const EquipmentInfo& equipment);
void printMenu();
void readAndPrintFromFile();
void deleteAllData();

const string fileName = "equipments.dat";

int main() {
    vector<EquipmentInfo> equipments;
    int choice;
    char continueChoice;

    loadFromFile(equipments); // 加载现有设备信息

    do {
        system("cls"); // 清屏
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            do {
                inputEquipmentInfo(equipments);
                std::cout << "\n是否继续输入设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;

        case 2:
            do {
                addEquipment(equipments);
                std::cout << "\n是否继续添加设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 3:
            do {
                modifyEquipment(equipments);
                std::cout << "\n是否继续修改设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 4:
            do {
                searchEquipment(equipments);
                std::cout << "\n是否继续查询设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
         case 5:
             do {
                 deleteEquipment(equipments);
                 std::cout << "\n是否继续删除设备信息？(y/n): ";
                 cin >> continueChoice;
             } while (continueChoice == 'y' || continueChoice == 'Y'); 
            break;
        case 6:
            do {
                classifyEquipment(equipments);
                std::cout << "\n是否继续统计设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 7:
            do {
                readAndPrintFromFile();
                std::cout << "\n是否继续打印当前所有设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 8:
            do {
                deleteAllData();
                std::cout << "\n是否格式化所有设备信息？(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        default:
            break;
        }
        saveToFile(equipments);
        
    } while (choice != 0);

    return 0;
}
void clearScreen() {
    system("cls");  // 清屏
}
void printMenu() {
    
    std::cout << "============================================\n";
    std::cout << "           实验设备信息管理系统\n";
    std::cout << "============================================\n";
    std::cout << "\t[1] 输入设备信息\n";
    std::cout << "\t[2] 添加设备信息\n";
    std::cout << "\t[3] 修改设备信息\n";
    std::cout << "\t[4] 查询设备信息\n";
    std::cout << "\t[5] 删除设备信息\n";
    std::cout << "\t[6] 统计设备信息\n";
    std::cout << "\t[7] 显示所有设备信息\n";
    std::cout << "\t[8] 格式化所有设备信息\n";
    std::cout << "\t[0] 退出\n";
    std::cout << "============================================\n";
    std::cout << "请选择操作: ";
}
void printEquipment(const EquipmentInfo& equipment) {
    std::cout << "============================================\n";
    std::cout << "               实验设备信息\n";
    std::cout << "============================================\n";
    std::cout << "\t设备编号: "<< equipment.equipCode << endl;
    std::cout << "\t设备类型: "<< equipment.equipType << endl;
    std::cout << "\t设备名称: "<< equipment.equipName << endl;
    std::cout << "\t设备价格: "<< equipment.equipPrice << endl;
    std::cout << "\t购入日期: " << equipment.buyDate << endl;
    std::cout << "\t是否报废: " << (equipment.scrap ? "是" : "否") <<endl;
    if (equipment.scrap) {
        std::cout << "\t报废日期: " << equipment.scrapDate << endl;
    }
    std::cout << "============================================\n";
}
void printEquipment1() {
    std::cout << "\n=============================================================================================================================\n";
    std::cout << "\t设备编号: " << "\t设备种类: " << "\t设备名称: " << "\t\t设备价格: " << "\t购入日期: " << "\t设备状态: " << "\t设备报废日期: \n";
}
void printEquipment2(const EquipmentInfo& equipment) {
    std::cout << "\t" << equipment.equipCode << "\t\t" << equipment.equipType << "\t\t" << setw(21) << left << equipment.equipName << "\t" << equipment.equipPrice << "\t\t" << equipment.buyDate << "\t" << (equipment.scrap ? "已报废" : "未报废") << "\t\t" << equipment.scrapDate << endl;
    }
bool isEquipCodeExist(const vector<EquipmentInfo>& equipments, const string& code) {
    for (const auto& equipment : equipments) {
        if (equipment.equipCode == code) {
            return true;
        }
    }
    return false;
}
void inputEquipmentInfo(std::vector<EquipmentInfo>& equipments) {
    EquipmentInfo newEquip;
    string inputCode;
    system("cls");
    std::cout << "============================================\n";
    std::cout << "\t输入设备编号: ";
    cin >> inputCode;
    while (isEquipCodeExist(equipments, inputCode)) {
        std::cout << "\t当前设备编码已经被使用\n\t请重新输入设备编号: ";
        cin >> inputCode;
    }
    strncpy(newEquip.equipCode, inputCode.c_str(), sizeof(newEquip.equipCode));
    newEquip.equipCode[sizeof(newEquip.equipCode) - 1] = '\0';
    std::cout << "\t输入设备种类: ";
    cin >> newEquip.equipType;
    std::cout << "\t输入设备名称: ";
    cin >> newEquip.equipName;
    std::cout << "\t输入设备价格: ";
    cin >> newEquip.equipPrice;
    std::cout << "\t输入购入日期: ";
    std::cin >> newEquip.buyDate;
    std::cout << "\t设备状态(0:正常，1：报废):";
    std::cin >> newEquip.scrap; // 默认未报废
    if (newEquip.scrap == 0)
        strcpy_s(newEquip.scrapDate, "N/A"); // 默认报废日期为N/A
    else {
        std::cout << "\t请输入报废日期：";
        std::cin >> newEquip.scrapDate;
    }
    std::cout << "============================================\n";
    std::cout << "最新输入的设备信息为：\n" << "\t设备编号:" << newEquip.equipCode << "\n\t设备种类: "
        << newEquip.equipType << "\n\t设备名称: " << newEquip.equipName << "\n\t设备价格: "
        << newEquip.equipPrice << "\n\t购入日期: " << newEquip.buyDate << "\n\t设备状态："
        << newEquip.scrap << "\n\t设备报废日期：" << newEquip.scrapDate << endl;
    saveToFile(equipments);
}
void addEquipment(std::vector<EquipmentInfo>& equipments) {
        EquipmentInfo newEquip;
        string inputCode;
        std::cout << "============================================\n";
        std::cout << "请输入要添加的信息\n";
        std::cout << "\t输入设备编号: ";
        cin >> inputCode;
        while (isEquipCodeExist(equipments, inputCode)) {
            std::cout << "\t当前设备编码已经被使用\n\t请重新输入设备编号: ";
            cin >> inputCode;
        }
        strncpy(newEquip.equipCode, inputCode.c_str(), sizeof(newEquip.equipCode));
        newEquip.equipCode[sizeof(newEquip.equipCode) - 1] = '\0';
            std::cout << "\t输入设备种类: ";
            cin >> newEquip.equipType;
            std::cout << "\t输入设备名称: ";
            cin >> newEquip.equipName;
            std::cout << "\t输入设备价格: ";
            cin >> newEquip.equipPrice;
            std::cout << "\t输入购入日期: ";
            std::cin >> newEquip.buyDate;
            std::cout << "\t设备状态(0:正常，1：报废):";
            std::cin>>newEquip.scrap ; // 默认未报废
            if(newEquip.scrap==0)
                strcpy_s(newEquip.scrapDate, "N/A"); // 默认报废日期为N/A
            else {
                std::cout << "\t请输入报废日期：";
                std::cin >> newEquip.scrapDate;
            }
        std::cout << "============================================\n";
        std::cout << "追加输入的设备信息为：\n" << "\t设备编号:" << newEquip.equipCode << "\n\t设备种类: "
            << newEquip.equipType << "\n\t设备名称: " << newEquip.equipName << "\n\t设备价格: "
            << newEquip.equipPrice << "\n\t购入日期: " << newEquip.buyDate << "\n\t设备状态："
            << newEquip.scrap << "\n\t设备报废日期：" << newEquip.scrapDate << endl;
        equipments.push_back(newEquip); // 将新设备信息添加到向量中

        std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out | std::ios::app);

        if (!file) {
            std::cerr << "无法打开文件进行写入\n";
            return;
        }

        file.write(reinterpret_cast<const char*>(&newEquip), sizeof(EquipmentInfo));
        file.close();

        std::cout << "设备信息已添加。\n";
}

void modifyMenu() {
    std::cout << "============================================\n";
    std::cout << "           请选择要修改的信息          " << endl;
    std::cout << "\t1. 修改设备编号:" << endl;
    std::cout << "\t2. 修改设备种类:" << endl;
    std::cout << "\t3. 修改设备名称:" << endl;
    std::cout << "\t4. 修改设备价格:" << endl;
    std::cout << "\t5. 修改设备购入日期:" << endl;
    std::cout << "\t6. 修改设备状态:" << endl;
    std::cout << "============================================\n";
}
void modifyEquipment(vector<EquipmentInfo>& equipments) {
    char code[10];
    system("cls");
    std::cout << "\t输入要修改的设备编号: ";
    cin >> code;
    int chioce;
    for (auto& equipment : equipments) {// 修改设备信息
        if (strcmp(equipment.equipCode, code) == 0) {
            std::cout << "找到设备，当前信息：" << endl;
            printEquipment(equipment);
            modifyMenu();
            cin >> chioce;
            switch (chioce) {
            case 1: {
                std::cout << "============================================\n";
                string inputCode;
                std::cout << "输入新的设备编号: ";
                cin >> inputCode;
                while (isEquipCodeExist(equipments, inputCode)) {
                    std::cout << "\t当前设备编码已经被使用\n\t请重新输入设备编号: ";
                    cin >> inputCode;
                }
                std::cout << endl << "修改成功" << endl;
                std::cout << "当前设备编号为" << inputCode << endl;
                std::cout << "============================================\n";
                break; }
            case 2: {
                std::cout << "============================================\n";
                std::cout << "输入新的设备种类: ";
                cin >> equipment.equipType;
                std::cout << endl << "修改成功" << endl << "当前设备种类为" << equipment.equipType << endl;
                std::cout << "============================================\n";
                break; }
            case 3: {
                std::cout << "============================================\n";
                std::cout << "输入新的设备名称: ";
                cin >> equipment.equipName;
                std::cout << endl << "修改成功" << endl << "当前设备名称为" << equipment.equipName << endl;
                std::cout << "============================================\n";
                break; }
            case 4: {
                std::cout << "============================================\n";
                std::cout << "输入新的设备价格: ";
                cin >> equipment.equipPrice;
                std::cout << endl << "修改成功" << endl << "当前设备价格为" << equipment.equipPrice << endl;
                std::cout << "============================================\n";
                break; }
            case 5: {
                std::cout << "============================================\n";
                std::cout << "输入新的购入日期: ";
                cin >> equipment.buyDate;
                std::cout << endl << "修改成功" << endl << "当前设备购入日期为" << equipment.buyDate << endl;
                std::cout << "============================================\n";
                break; }
            case 6: {
                std::cout << "============================================\n";
                std::cout << "设备是否报废（0-否，1-是）: ";
                cin >> equipment.scrap;
                if (equipment.scrap) {
                    std::cout << "输入报废日期: ";
                    cin >> equipment.scrapDate;
                    std::cout << "当前设备以报废" << endl << "报废日期为" << equipment.scrapDate << endl;
                    std::cout << "============================================\n";
                    break;
                }
                else {
                    strcpy_s(equipment.scrapDate, "N/A");
                    std::cout << "修改成功" << endl << "设备完好可正常使用\n";
                    std::cout << "============================================\n";
                }
                return;

            }
            default:
                break;
            }
        if((strcmp(equipment.equipCode, code)< 0)|(strcmp(equipment.equipCode, code) > 0)){
            std::cout << "\t未找到设备编号为 " << code << " 的设备。" << endl;
            std::cout << "\t你输入的此段信息将直接写入文件。\n";
            addEquipment(equipments);
            break;
        }
        }
    }
}
void queryMenu() {
    std::cout << "============================================\n";
    std::cout << "               查询方式:\n";
    std::cout << "============================================\n";
    std::cout << "[B] 按设备编号查询:\n" ;
    std::cout << "[T] 按设备种类查询:\n" ;
    std::cout << "[N] 按设备名称查询:\n" ;
    std::cout << "[D] 按设备购入日期查询:\n";
    std::cout << "[S] 按设备状态查询:\n";
    std::cout << "\n============================================\n";
    std::cout << "请选择查询类型: ";
}

void saveToFile(const vector<EquipmentInfo>& equipments) {
    std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out);

    if (!file) {
        std::cerr << "无法打开文件进行写入\n";
        return;
    }
    for (const auto& equip : equipments) {
        file.write(reinterpret_cast<const char*>(&equip), sizeof(EquipmentInfo));
    }
    file.close();
    std::cout << "设备信息已添加。\n";
}

void loadFromFile(vector<EquipmentInfo>&equipments) {// 从文件读取设备信息的代码
    ifstream in("equipment_data.bin", std::ios::binary);
    if (!in) {
        cerr << "无法打开文件 " << "equipment_data.bin" << " 进行读取。可能是首次运行，文件还未创建。" << endl;
        return;
    }
    EquipmentInfo temp;
    while (in.read((char*)&temp, sizeof(EquipmentInfo))) {
        equipments.push_back(temp);
    }
    in.close();
}
void readAndPrintFromFile() {
    std::ifstream file("equipment_data.bin", std::ios::binary | std::ios::ate);

    if (!file) {
        std::cerr << "无法打开文件进行读取\n";
        return;
    }
    // 检查文件是否为空
    if (file.tellg() == 0) {
        std::cout << "文件为空，没有数据可读取。\n";
        file.close();
        return;
    }

    // 重置文件读取位置到文件开头
    file.seekg(0, std::ios::beg);

    EquipmentInfo equip;
    printEquipment1();
    while (file.read(reinterpret_cast<char*>(&equip), sizeof(EquipmentInfo))) {
        std::cout <<"\t" << equip.equipCode << "\t\t" << equip.equipType << "\t\t" <<setw(21)<<left<< equip.equipName << "\t" << equip.equipPrice << "\t\t" << equip.buyDate << "\t" << (equip.scrap ? "已报废" : "未报废") << "\t\t" << equip.scrapDate<<"\n";
    }
    file.close();
}

void searchEquipment(const vector<EquipmentInfo>& equipments) {
    char searchType;
    system("cls");
        queryMenu();
        cin >> searchType;
        switch (searchType) {
        case 'b' : 
        case 'B':{
            char code[10];
            std::cout << "输入设备编号: ";
            cin >> code;
            bool found = false;
            printEquipment1();
            for (const auto& equipment : equipments) {
                if (strcmp(equipment.equipCode, code) == 0) {
                    printEquipment2(equipment);
                    std::cout << endl;
                    found = true;
                }
            }
            if (!found) {
                std::cout << "没有找到编号为 " << code << " 的设备。" << endl;
            }
            break;
        }
        case 't':
        case'T': {
            char type[20];
            std::cout << "输入设备类型: ";
            cin >> type;

            bool found = false;
            printEquipment1();
            for (const auto& equipment : equipments) {
                if (strcmp(equipment.equipType, type) == 0) {
                    printEquipment2(equipment);
                    found = true;
                }
            }

            if (!found) {
                std::cout << "没有找到类型为 " << type << " 的设备。" << endl;
            }
            break;
        }
        case 'n':
        case 'N': { // 按名称查询
            char name[20];
            std::cout << "输入设备名称: ";
            cin >> name;

            bool found = false;
            printEquipment1();
            for (const auto& equipment : equipments) {
                if (strcmp(equipment.equipName, name) == 0) {
                    printEquipment2(equipment);
                    found = true;
                }
            }

            if (!found) {
                std::cout << "没有找到名称为 " << name << " 的设备。" << endl;
            }
            break;
        }
        case 'd':
        case'D': {
            char date[20];
            std::cout << "输入设备购入日期: ";
            cin >> date;

            bool found = false;
            printEquipment1();
            for (const auto& equipment : equipments) {
                if (strcmp(equipment.buyDate, date) == 0) {
                    printEquipment2(equipment);
                    found = true;
                }
            }

            if (!found) {
                std::cout << "没有找到类型为 " << date<< " 的设备。" << endl;
            }
            break;
        }
        case 's':
        case'S': {
            int scrap;
            std::cout << "输入设备状态（0:正常 或 1：报废）: ";
            std::cin >> scrap;
            bool found = false;
            printEquipment1();
            for (const auto& equipment : equipments) {
                if (equipment.scrap==scrap) {
                    printEquipment2(equipment);
                    found = true;
                }
            }

                if (!found) {
                    std::cout << "没有找到类型为 " << scrap << " 的设备。" << endl;
                }
                  break;
        }
        default:
            std::cout << "无效的查询类型。" << endl;
            break;
        }
}
void deleteEquipment(vector<EquipmentInfo>& equipments) {
    char code[10];
    system("cls");
    std::cout << "输入要删除的设备编号: ";
    cin >> code;
    bool found = false;
    for (const auto& equipment : equipments) {
        if (strcmp(equipment.equipCode, code) == 0) {
            std::cout <<"设备编号为" << code << "的设备信息为:\n";
            printEquipment(equipment);
            std::cout << endl;
            found = true;     
        }
    }
    auto it = find_if(equipments.begin(), equipments.end(),
        [code](const EquipmentInfo& equipment) {
            return strcmp(equipment.equipCode, code) == 0;
            
        });

    if (it != equipments.end()) {
        equipments.erase(it);
        std::cout <<"该设备信息已被删除。" << endl;
    }
    else {
        std::cout << "未找到编号为 " << code << " 的设备。" << endl;
    }
}
void deleteAllData() {
    std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out | std::ios::trunc);

    if (!file) {
        std::cerr << "无法打开文件进行写入\n";
        return;
    }

    file.close(); // 关闭文件，此时文件内容已被清空

    std::cout << "所有信息已删除。\n";
}
void classifyEquipment(const vector<EquipmentInfo>& equipments) {
    std::cout << "=======================================";
    std::cout << "\n设备分类统计：" << endl;
    map<string, pair<int, float>> stats; // 存储每个类型的数量和总价值

    for (const auto& equipment : equipments) {
        string type = equipment.equipType;
        stats[type].first += 1; // 数量加一
        stats[type].second += equipment.equipPrice; // 累加价格
    }
    for (const auto& entry : stats) {
        std::cout << "类型: " << entry.first << "\t数量: " << entry.second.first;
        std::cout << "\t总价值: " << entry.second.second << endl;
    }
}