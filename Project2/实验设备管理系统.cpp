#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include<map>
#pragma warning(disable : 4996)
using namespace std;

// �豸��Ϣ�ṹ��
struct EquipmentInfo {
    char equipCode[10];  // �豸���
    char equipType[20];  // �豸����
    char equipName[20];  // �豸����
    float equipPrice;    // �豸�۸�
    char buyDate[20];    // �豸��������
    int scrap;           // �Ƿ񱨷�
    char scrapDate[20];  // ��������
};

// ��������
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

    loadFromFile(equipments); // ���������豸��Ϣ

    do {
        system("cls"); // ����
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            do {
                inputEquipmentInfo(equipments);
                std::cout << "\n�Ƿ���������豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;

        case 2:
            do {
                addEquipment(equipments);
                std::cout << "\n�Ƿ��������豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 3:
            do {
                modifyEquipment(equipments);
                std::cout << "\n�Ƿ�����޸��豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 4:
            do {
                searchEquipment(equipments);
                std::cout << "\n�Ƿ������ѯ�豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
         case 5:
             do {
                 deleteEquipment(equipments);
                 std::cout << "\n�Ƿ����ɾ���豸��Ϣ��(y/n): ";
                 cin >> continueChoice;
             } while (continueChoice == 'y' || continueChoice == 'Y'); 
            break;
        case 6:
            do {
                classifyEquipment(equipments);
                std::cout << "\n�Ƿ����ͳ���豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 7:
            do {
                readAndPrintFromFile();
                std::cout << "\n�Ƿ������ӡ��ǰ�����豸��Ϣ��(y/n): ";
                cin >> continueChoice;
            } while (continueChoice == 'y' || continueChoice == 'Y');
            break;
        case 8:
            do {
                deleteAllData();
                std::cout << "\n�Ƿ��ʽ�������豸��Ϣ��(y/n): ";
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
    system("cls");  // ����
}
void printMenu() {
    
    std::cout << "============================================\n";
    std::cout << "           ʵ���豸��Ϣ����ϵͳ\n";
    std::cout << "============================================\n";
    std::cout << "\t[1] �����豸��Ϣ\n";
    std::cout << "\t[2] ����豸��Ϣ\n";
    std::cout << "\t[3] �޸��豸��Ϣ\n";
    std::cout << "\t[4] ��ѯ�豸��Ϣ\n";
    std::cout << "\t[5] ɾ���豸��Ϣ\n";
    std::cout << "\t[6] ͳ���豸��Ϣ\n";
    std::cout << "\t[7] ��ʾ�����豸��Ϣ\n";
    std::cout << "\t[8] ��ʽ�������豸��Ϣ\n";
    std::cout << "\t[0] �˳�\n";
    std::cout << "============================================\n";
    std::cout << "��ѡ�����: ";
}
void printEquipment(const EquipmentInfo& equipment) {
    std::cout << "============================================\n";
    std::cout << "               ʵ���豸��Ϣ\n";
    std::cout << "============================================\n";
    std::cout << "\t�豸���: "<< equipment.equipCode << endl;
    std::cout << "\t�豸����: "<< equipment.equipType << endl;
    std::cout << "\t�豸����: "<< equipment.equipName << endl;
    std::cout << "\t�豸�۸�: "<< equipment.equipPrice << endl;
    std::cout << "\t��������: " << equipment.buyDate << endl;
    std::cout << "\t�Ƿ񱨷�: " << (equipment.scrap ? "��" : "��") <<endl;
    if (equipment.scrap) {
        std::cout << "\t��������: " << equipment.scrapDate << endl;
    }
    std::cout << "============================================\n";
}
void printEquipment1() {
    std::cout << "\n=============================================================================================================================\n";
    std::cout << "\t�豸���: " << "\t�豸����: " << "\t�豸����: " << "\t\t�豸�۸�: " << "\t��������: " << "\t�豸״̬: " << "\t�豸��������: \n";
}
void printEquipment2(const EquipmentInfo& equipment) {
    std::cout << "\t" << equipment.equipCode << "\t\t" << equipment.equipType << "\t\t" << setw(21) << left << equipment.equipName << "\t" << equipment.equipPrice << "\t\t" << equipment.buyDate << "\t" << (equipment.scrap ? "�ѱ���" : "δ����") << "\t\t" << equipment.scrapDate << endl;
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
    std::cout << "\t�����豸���: ";
    cin >> inputCode;
    while (isEquipCodeExist(equipments, inputCode)) {
        std::cout << "\t��ǰ�豸�����Ѿ���ʹ��\n\t�����������豸���: ";
        cin >> inputCode;
    }
    strncpy(newEquip.equipCode, inputCode.c_str(), sizeof(newEquip.equipCode));
    newEquip.equipCode[sizeof(newEquip.equipCode) - 1] = '\0';
    std::cout << "\t�����豸����: ";
    cin >> newEquip.equipType;
    std::cout << "\t�����豸����: ";
    cin >> newEquip.equipName;
    std::cout << "\t�����豸�۸�: ";
    cin >> newEquip.equipPrice;
    std::cout << "\t���빺������: ";
    std::cin >> newEquip.buyDate;
    std::cout << "\t�豸״̬(0:������1������):";
    std::cin >> newEquip.scrap; // Ĭ��δ����
    if (newEquip.scrap == 0)
        strcpy_s(newEquip.scrapDate, "N/A"); // Ĭ�ϱ�������ΪN/A
    else {
        std::cout << "\t�����뱨�����ڣ�";
        std::cin >> newEquip.scrapDate;
    }
    std::cout << "============================================\n";
    std::cout << "����������豸��ϢΪ��\n" << "\t�豸���:" << newEquip.equipCode << "\n\t�豸����: "
        << newEquip.equipType << "\n\t�豸����: " << newEquip.equipName << "\n\t�豸�۸�: "
        << newEquip.equipPrice << "\n\t��������: " << newEquip.buyDate << "\n\t�豸״̬��"
        << newEquip.scrap << "\n\t�豸�������ڣ�" << newEquip.scrapDate << endl;
    saveToFile(equipments);
}
void addEquipment(std::vector<EquipmentInfo>& equipments) {
        EquipmentInfo newEquip;
        string inputCode;
        std::cout << "============================================\n";
        std::cout << "������Ҫ��ӵ���Ϣ\n";
        std::cout << "\t�����豸���: ";
        cin >> inputCode;
        while (isEquipCodeExist(equipments, inputCode)) {
            std::cout << "\t��ǰ�豸�����Ѿ���ʹ��\n\t�����������豸���: ";
            cin >> inputCode;
        }
        strncpy(newEquip.equipCode, inputCode.c_str(), sizeof(newEquip.equipCode));
        newEquip.equipCode[sizeof(newEquip.equipCode) - 1] = '\0';
            std::cout << "\t�����豸����: ";
            cin >> newEquip.equipType;
            std::cout << "\t�����豸����: ";
            cin >> newEquip.equipName;
            std::cout << "\t�����豸�۸�: ";
            cin >> newEquip.equipPrice;
            std::cout << "\t���빺������: ";
            std::cin >> newEquip.buyDate;
            std::cout << "\t�豸״̬(0:������1������):";
            std::cin>>newEquip.scrap ; // Ĭ��δ����
            if(newEquip.scrap==0)
                strcpy_s(newEquip.scrapDate, "N/A"); // Ĭ�ϱ�������ΪN/A
            else {
                std::cout << "\t�����뱨�����ڣ�";
                std::cin >> newEquip.scrapDate;
            }
        std::cout << "============================================\n";
        std::cout << "׷��������豸��ϢΪ��\n" << "\t�豸���:" << newEquip.equipCode << "\n\t�豸����: "
            << newEquip.equipType << "\n\t�豸����: " << newEquip.equipName << "\n\t�豸�۸�: "
            << newEquip.equipPrice << "\n\t��������: " << newEquip.buyDate << "\n\t�豸״̬��"
            << newEquip.scrap << "\n\t�豸�������ڣ�" << newEquip.scrapDate << endl;
        equipments.push_back(newEquip); // �����豸��Ϣ��ӵ�������

        std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out | std::ios::app);

        if (!file) {
            std::cerr << "�޷����ļ�����д��\n";
            return;
        }

        file.write(reinterpret_cast<const char*>(&newEquip), sizeof(EquipmentInfo));
        file.close();

        std::cout << "�豸��Ϣ����ӡ�\n";
}

void modifyMenu() {
    std::cout << "============================================\n";
    std::cout << "           ��ѡ��Ҫ�޸ĵ���Ϣ          " << endl;
    std::cout << "\t1. �޸��豸���:" << endl;
    std::cout << "\t2. �޸��豸����:" << endl;
    std::cout << "\t3. �޸��豸����:" << endl;
    std::cout << "\t4. �޸��豸�۸�:" << endl;
    std::cout << "\t5. �޸��豸��������:" << endl;
    std::cout << "\t6. �޸��豸״̬:" << endl;
    std::cout << "============================================\n";
}
void modifyEquipment(vector<EquipmentInfo>& equipments) {
    char code[10];
    system("cls");
    std::cout << "\t����Ҫ�޸ĵ��豸���: ";
    cin >> code;
    int chioce;
    for (auto& equipment : equipments) {// �޸��豸��Ϣ
        if (strcmp(equipment.equipCode, code) == 0) {
            std::cout << "�ҵ��豸����ǰ��Ϣ��" << endl;
            printEquipment(equipment);
            modifyMenu();
            cin >> chioce;
            switch (chioce) {
            case 1: {
                std::cout << "============================================\n";
                string inputCode;
                std::cout << "�����µ��豸���: ";
                cin >> inputCode;
                while (isEquipCodeExist(equipments, inputCode)) {
                    std::cout << "\t��ǰ�豸�����Ѿ���ʹ��\n\t�����������豸���: ";
                    cin >> inputCode;
                }
                std::cout << endl << "�޸ĳɹ�" << endl;
                std::cout << "��ǰ�豸���Ϊ" << inputCode << endl;
                std::cout << "============================================\n";
                break; }
            case 2: {
                std::cout << "============================================\n";
                std::cout << "�����µ��豸����: ";
                cin >> equipment.equipType;
                std::cout << endl << "�޸ĳɹ�" << endl << "��ǰ�豸����Ϊ" << equipment.equipType << endl;
                std::cout << "============================================\n";
                break; }
            case 3: {
                std::cout << "============================================\n";
                std::cout << "�����µ��豸����: ";
                cin >> equipment.equipName;
                std::cout << endl << "�޸ĳɹ�" << endl << "��ǰ�豸����Ϊ" << equipment.equipName << endl;
                std::cout << "============================================\n";
                break; }
            case 4: {
                std::cout << "============================================\n";
                std::cout << "�����µ��豸�۸�: ";
                cin >> equipment.equipPrice;
                std::cout << endl << "�޸ĳɹ�" << endl << "��ǰ�豸�۸�Ϊ" << equipment.equipPrice << endl;
                std::cout << "============================================\n";
                break; }
            case 5: {
                std::cout << "============================================\n";
                std::cout << "�����µĹ�������: ";
                cin >> equipment.buyDate;
                std::cout << endl << "�޸ĳɹ�" << endl << "��ǰ�豸��������Ϊ" << equipment.buyDate << endl;
                std::cout << "============================================\n";
                break; }
            case 6: {
                std::cout << "============================================\n";
                std::cout << "�豸�Ƿ񱨷ϣ�0-��1-�ǣ�: ";
                cin >> equipment.scrap;
                if (equipment.scrap) {
                    std::cout << "���뱨������: ";
                    cin >> equipment.scrapDate;
                    std::cout << "��ǰ�豸�Ա���" << endl << "��������Ϊ" << equipment.scrapDate << endl;
                    std::cout << "============================================\n";
                    break;
                }
                else {
                    strcpy_s(equipment.scrapDate, "N/A");
                    std::cout << "�޸ĳɹ�" << endl << "�豸��ÿ�����ʹ��\n";
                    std::cout << "============================================\n";
                }
                return;

            }
            default:
                break;
            }
        if((strcmp(equipment.equipCode, code)< 0)|(strcmp(equipment.equipCode, code) > 0)){
            std::cout << "\tδ�ҵ��豸���Ϊ " << code << " ���豸��" << endl;
            std::cout << "\t������Ĵ˶���Ϣ��ֱ��д���ļ���\n";
            addEquipment(equipments);
            break;
        }
        }
    }
}
void queryMenu() {
    std::cout << "============================================\n";
    std::cout << "               ��ѯ��ʽ:\n";
    std::cout << "============================================\n";
    std::cout << "[B] ���豸��Ų�ѯ:\n" ;
    std::cout << "[T] ���豸�����ѯ:\n" ;
    std::cout << "[N] ���豸���Ʋ�ѯ:\n" ;
    std::cout << "[D] ���豸�������ڲ�ѯ:\n";
    std::cout << "[S] ���豸״̬��ѯ:\n";
    std::cout << "\n============================================\n";
    std::cout << "��ѡ���ѯ����: ";
}

void saveToFile(const vector<EquipmentInfo>& equipments) {
    std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out);

    if (!file) {
        std::cerr << "�޷����ļ�����д��\n";
        return;
    }
    for (const auto& equip : equipments) {
        file.write(reinterpret_cast<const char*>(&equip), sizeof(EquipmentInfo));
    }
    file.close();
    std::cout << "�豸��Ϣ����ӡ�\n";
}

void loadFromFile(vector<EquipmentInfo>&equipments) {// ���ļ���ȡ�豸��Ϣ�Ĵ���
    ifstream in("equipment_data.bin", std::ios::binary);
    if (!in) {
        cerr << "�޷����ļ� " << "equipment_data.bin" << " ���ж�ȡ���������״����У��ļ���δ������" << endl;
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
        std::cerr << "�޷����ļ����ж�ȡ\n";
        return;
    }
    // ����ļ��Ƿ�Ϊ��
    if (file.tellg() == 0) {
        std::cout << "�ļ�Ϊ�գ�û�����ݿɶ�ȡ��\n";
        file.close();
        return;
    }

    // �����ļ���ȡλ�õ��ļ���ͷ
    file.seekg(0, std::ios::beg);

    EquipmentInfo equip;
    printEquipment1();
    while (file.read(reinterpret_cast<char*>(&equip), sizeof(EquipmentInfo))) {
        std::cout <<"\t" << equip.equipCode << "\t\t" << equip.equipType << "\t\t" <<setw(21)<<left<< equip.equipName << "\t" << equip.equipPrice << "\t\t" << equip.buyDate << "\t" << (equip.scrap ? "�ѱ���" : "δ����") << "\t\t" << equip.scrapDate<<"\n";
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
            std::cout << "�����豸���: ";
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
                std::cout << "û���ҵ����Ϊ " << code << " ���豸��" << endl;
            }
            break;
        }
        case 't':
        case'T': {
            char type[20];
            std::cout << "�����豸����: ";
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
                std::cout << "û���ҵ�����Ϊ " << type << " ���豸��" << endl;
            }
            break;
        }
        case 'n':
        case 'N': { // �����Ʋ�ѯ
            char name[20];
            std::cout << "�����豸����: ";
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
                std::cout << "û���ҵ�����Ϊ " << name << " ���豸��" << endl;
            }
            break;
        }
        case 'd':
        case'D': {
            char date[20];
            std::cout << "�����豸��������: ";
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
                std::cout << "û���ҵ�����Ϊ " << date<< " ���豸��" << endl;
            }
            break;
        }
        case 's':
        case'S': {
            int scrap;
            std::cout << "�����豸״̬��0:���� �� 1�����ϣ�: ";
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
                    std::cout << "û���ҵ�����Ϊ " << scrap << " ���豸��" << endl;
                }
                  break;
        }
        default:
            std::cout << "��Ч�Ĳ�ѯ���͡�" << endl;
            break;
        }
}
void deleteEquipment(vector<EquipmentInfo>& equipments) {
    char code[10];
    system("cls");
    std::cout << "����Ҫɾ�����豸���: ";
    cin >> code;
    bool found = false;
    for (const auto& equipment : equipments) {
        if (strcmp(equipment.equipCode, code) == 0) {
            std::cout <<"�豸���Ϊ" << code << "���豸��ϢΪ:\n";
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
        std::cout <<"���豸��Ϣ�ѱ�ɾ����" << endl;
    }
    else {
        std::cout << "δ�ҵ����Ϊ " << code << " ���豸��" << endl;
    }
}
void deleteAllData() {
    std::ofstream file("equipment_data.bin", std::ios::binary | std::ios::out | std::ios::trunc);

    if (!file) {
        std::cerr << "�޷����ļ�����д��\n";
        return;
    }

    file.close(); // �ر��ļ�����ʱ�ļ������ѱ����

    std::cout << "������Ϣ��ɾ����\n";
}
void classifyEquipment(const vector<EquipmentInfo>& equipments) {
    std::cout << "=======================================";
    std::cout << "\n�豸����ͳ�ƣ�" << endl;
    map<string, pair<int, float>> stats; // �洢ÿ�����͵��������ܼ�ֵ

    for (const auto& equipment : equipments) {
        string type = equipment.equipType;
        stats[type].first += 1; // ������һ
        stats[type].second += equipment.equipPrice; // �ۼӼ۸�
    }
    for (const auto& entry : stats) {
        std::cout << "����: " << entry.first << "\t����: " << entry.second.first;
        std::cout << "\t�ܼ�ֵ: " << entry.second.second << endl;
    }
}