#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// 定義學生結構體
struct Student {
    string name;      // 學生姓名
    int score;        // 學生成績
};

// 全域向量存儲所有學生
vector<Student> students;

// ===================== 函式宣告 =====================

// 新增學生
void addStudent();

// 顯示所有學生
void displayAllStudents();

// 查詢學生
void searchStudent();

// 計算平均成績
void calculateAverage();

// 顯示最高分與最低分
void showHighestLowest();

// 依成績由高到低排序
void sortByScore();

// 儲存資料到檔案
void saveToFile();

// 從檔案讀取資料
void loadFromFile();

// 顯示主選單
void showMenu();

// ===================== 函式實現 =====================

/**
 * 新增學生函式
 * 提示使用者輸入學生姓名和成績，並新增至 vector 中
 */
void addStudent() {
    cout << "\n========== 新增學生 ==========" << endl;
    
    string name;
    int score;
    
    cout << "請輸入學生姓名: ";
    cin >> name;
    
    cout << "請輸入成績 (0-100): ";
    cin >> score;
    
    // 驗證成績範圍
    if (score < 0 || score > 100) {
        cout << "❌ 成績必須在 0-100 之間！" << endl;
        return;
    }
    
    // 檢查是否已存在相同姓名的學生
    for (const auto& student : students) {
        if (student.name == name) {
            cout << "❌ 該學生已存在！" << endl;
            return;
        }
    }
    
    students.push_back({name, score});
    cout << "✓ 學生新增成功！" << endl;
}

/**
 * 顯示所有學生函式
 * 以表格形式顯示所有學生的姓名和成績
 */
void displayAllStudents() {
    cout << "\n========== 所有學生列表 ==========" << endl;
    
    if (students.empty()) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    
    cout << left << setw(20) << "姓名" << setw(15) << "成績" << endl;
    cout << string(35, '-') << endl;
    
    for (const auto& student : students) {
        cout << left << setw(20) << student.name << setw(15) << student.score << endl;
    }
    
    cout << "\n總共 " << students.size() << " 位學生" << endl;
}

/**
 * 查詢學生函式
 * 根據學生姓名進行查詢
 */
void searchStudent() {
    cout << "\n========== 查詢學生 ==========" << endl;
    
    if (students.empty()) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    
    string searchName;
    cout << "請輸入要查詢的學生姓名: ";
    cin >> searchName;
    
    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            cout << "✓ 查詢結果：" << endl;
            cout << "姓名: " << student.name << endl;
            cout << "成績: " << student.score << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "❌ 找不到該學生！" << endl;
    }
}

/**
 * 計算平均成績函式
 * 計算所有學生成績的平均值
 */
void calculateAverage() {
    cout << "\n========== 計算平均成績 ==========" << endl;
    
    if (students.empty()) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    
    int totalScore = 0;
    for (const auto& student : students) {
        totalScore += student.score;
    }
    
    double average = static_cast<double>(totalScore) / students.size();
    
    cout << "平均成績: " << fixed << setprecision(2) << average << endl;
}

/**
 * 顯示最高分與最低分函式
 * 找出並顯示最高分和最低分的學生資訊
 */
void showHighestLowest() {
    cout << "\n========== 最高分與最低分 ==========" << endl;
    
    if (students.empty()) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    
    // 找最高分
    auto maxStudent = *max_element(students.begin(), students.end(),
                                   [](const Student& a, const Student& b) {
                                       return a.score < b.score;
                                   });
    
    // 找最低分
    auto minStudent = *min_element(students.begin(), students.end(),
                                   [](const Student& a, const Student& b) {
                                       return a.score < b.score;
                                   });
    
    cout << "最高分: " << maxStudent.name << " (" << maxStudent.score << "分)" << endl;
    cout << "最低分: " << minStudent.name << " (" << minStudent.score << "分)" << endl;
}

/**
 * 依成績由高到低排序函式
 * 使用標準庫的 sort 函式排序
 */
void sortByScore() {
    cout << "\n========== 排序完成 ==========" << endl;
    
    if (students.empty()) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.score > b.score;  // 由高到低排序
         });
    
    cout << "✓ 已按成績由高到低排序！" << endl;
    displayAllStudents();
}

/**
 * 儲存資料到檔案函式
 * 將所有學生資料寫入 student.txt 檔案
 */
void saveToFile() {
    cout << "\n========== 儲存資料 ==========" << endl;
    
    ofstream outFile("student.txt");
    
    if (!outFile.is_open()) {
        cout << "❌ 無法開啟檔案進行寫入！" << endl;
        return;
    }
    
    // 寫入學生數量
    outFile << students.size() << endl;
    
    // 寫入每個學生的資訊
    for (const auto& student : students) {
        outFile << student.name << " " << student.score << endl;
    }
    
    outFile.close();
    cout << "✓ 資料已成功儲存至 student.txt" << endl;
}

/**
 * 從檔案讀取資料函式
 * 從 student.txt 讀取學生資料
 */
void loadFromFile() {
    cout << "\n========== 讀取資料 ==========" << endl;
    
    ifstream inFile("student.txt");
    
    if (!inFile.is_open()) {
        cout << "⚠ 檔案不存在，將建立新檔案。" << endl;
        return;
    }
    
    students.clear();  // 清空現有資料
    
    int count;
    inFile >> count;
    
    for (int i = 0; i < count; i++) {
        string name;
        int score;
        inFile >> name >> score;
        students.push_back({name, score});
    }
    
    inFile.close();
    cout << "✓ 已成功讀取 " << count << " 位學生的資料！" << endl;
}

/**
 * 顯示主選單函式
 * 展示所有可用的功能選項
 */
void showMenu() {
    cout << "\n========================================" << endl;
    cout << "     學生成績管理系統 - 主選單" << endl;
    cout << "========================================" << endl;
    cout << "1. 新增學生" << endl;
    cout << "2. 顯示所有學生" << endl;
    cout << "3. 查詢學生" << endl;
    cout << "4. 計算平均成績" << endl;
    cout << "5. 顯示最高分與最低分" << endl;
    cout << "6. 依成績由高到低排序" << endl;
    cout << "7. 儲存資料到 student.txt" << endl;
    cout << "8. 從 student.txt 讀取資料" << endl;
    cout << "9. 離開程式" << endl;
    cout << "========================================" << endl;
}

/**
 * 主程式函式
 * 使用 switch-case 處理使用者選擇
 */
int main() {
    // 設置輸出編碼支持中文
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    cout << "歡迎使用學生成績管理系統！" << endl;
    
    // 自動從檔案讀取之前的資料
    ifstream checkFile("student.txt");
    if (checkFile.good()) {
        checkFile.close();
        loadFromFile();
    }
    
    int choice;
    
    while (true) {
        showMenu();
        cout << "請選擇功能 (1-9): ";
        
        // 驗證輸入
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ 無效輸入，請輸入數字！" << endl;
            continue;
        }
        
        // 使用 switch-case 處理選單
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                calculateAverage();
                break;
            case 5:
                showHighestLowest();
                break;
            case 6:
                sortByScore();
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                loadFromFile();
                break;
            case 9:
                cout << "\n感謝使用，再見！" << endl;
                return 0;
            default:
                cout << "❌ 無效選擇，請重新輸入！" << endl;
        }
    }
    
    return 0;
}
