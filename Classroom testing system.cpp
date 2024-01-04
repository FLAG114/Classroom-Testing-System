#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_QUESTIONS = 100; // 最大题目数量


class Question {
public:
    string content;
    string options[4];
    char answer;
};


class QuestionBank {
private:
    Question questions[MAX_QUESTIONS];


public:
    int numQuestions;
    QuestionBank() : numQuestions(0) {}

    void addQuestion(const Question& question) {
        if (numQuestions < MAX_QUESTIONS) {
            questions[numQuestions] = question;
            numQuestions++;
            cout << "题目添加成功！" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "题目库已满，无法添加更多题目！" << endl;
            system("pause");
            system("cls");
        }
    }

    Question* searchQuestion(const string& content) {
        for (int i = 0; i < numQuestions; i++) {
            if (questions[i].content == content) {
                return &questions[i];
            }
        }
        return nullptr;
    }

    void modifyQuestion(const string& content, const string& newContent, char newAnswer) {
        Question* question = searchQuestion(content);
        if (question != nullptr) {
            question->content = newContent;
            question->answer = newAnswer;
            cout << "题目修改成功！" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "未找到该题目！" << endl;
            system("pause");
            system("cls");
        }
    }

    Question getRandomQuestion() const {
        srand(time(nullptr));
        int index = rand() % numQuestions;
        return questions[index];
    }
};

// 测试系统类
class TestSystem {
private:
    QuestionBank questionBank;
    Question testQuestions[MAX_QUESTIONS];
    string username;
    int numTestQuestions;
    char userAnswers[MAX_QUESTIONS];

public:
    void addQuestion() {
        if (numTestQuestions >= MAX_QUESTIONS) {
            cout << "题目数量已达上限，无法添加更多题目！" << endl;
            system("pause");
            system("cls");
            return;
        }

        Question question;
        cout << "请输入题目内容：";
        getline(cin, question.content);

        for (int i = 0; i < 4; ++i) {
            cout << "请输入选项" << static_cast<char>('A' + i) << "：";
            getline(cin, question.options[i]);
        }

        cout << "请输入正确答案（A/B/C/D）：";
        cin >> question.answer;



        questionBank.addQuestion(question);
    }

    void modifyQuestion() {
        cout << "请输入要修改的题目内容：";
        string content;
        getline(cin, content);

        Question* question = questionBank.searchQuestion(content);
        if (question != nullptr) {
            cout << "找到题目：" << question->content << endl;
            cout << "请输入修改后的题目内容：";
            getline(cin, question->content);

            cout << "请输入修改后的答案（A/B/C/D）：";
            cin >> question->answer;

            cout << "题目修改成功！" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "未找到该题目！" << endl;
            system("pause");
            system("cls");
        }
    }

    void startTest() {
        if (questionBank.numQuestions == 0) {
            cout << "题目数量为零，无法进行测试！" << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << "请输入用户名：";
        getline(cin, username);

        cout << "请输入要测试的题目数量：";
        cin >> numTestQuestions;


        cout << "测试开始！" << endl;
        for (int i = 0; i < numTestQuestions; i++) {
            Question question = questionBank.getRandomQuestion();
            testQuestions[i] = question;
            cout << "第" << i + 1 << "题：" << question.content << endl;
            for (int j = 0; j < 4; j++) {
                cout << static_cast<char>('A' + j) << ". " << question.options[j] << endl;
            }

            cout << "请输入您的答案（A/B/C/D）：";
            cin >> userAnswers[i];

            // 检查答案是否正确
            if (userAnswers[i] == question.answer) {
                cout << "回答正确！" << endl;
            }
            else {
                cout << "回答错误！正确答案是：" << question.answer << endl;
            }

            char choice;
            cout << "是否继续答题？（Y/N）：";
            cin >> choice;
            if (toupper(choice) == 'N') {
                break;
            }
        }
        system("pause");
        system("cls");
    }

    void viewScore() {
        int score = 0;
        int wrongQuestionIndices[MAX_QUESTIONS];
        int numWrongQuestions = 0;
        cout << "请输入用户名：";
        getline(cin, username);

        for (int i = 0; i < numTestQuestions; i++) {
            Question question = testQuestions[i];

            if (toupper(testQuestions[i].answer) == toupper(userAnswers[i])) {
                score += (100 / numTestQuestions);
            }
            else {
                wrongQuestionIndices[numWrongQuestions] = i;
                numWrongQuestions++;
            }
        }

        cout << "用户名：" << username << endl;
        cout << "得分：" << score << endl;
        cout << "错题：";
        if (numWrongQuestions == 0) {
            cout << "无" << endl;
        }
        else {
            for (int i = 0; i < numWrongQuestions; i++) {
                int index = wrongQuestionIndices[i];
                Question question = testQuestions[index];
                cout << "第" << index + 1 << "题：" << question.content << endl;
                cout << "您的答案：" << userAnswers[index] << endl;
                cout << "正确答案：" << question.answer << endl;

                if (i < numWrongQuestions - 1) {
                    cout << endl;
                }
            }
        }
        system("pause");
        system("cls");
    }

    void showMenu() {
        cout << "欢迎使用课堂测试系统！" << endl;
        cout << "请选择功能：" << endl;
        cout << "1. 试题库录入" << endl;
        cout << "2. 试题库维护" << endl;
        cout << "3. 测试" << endl;
        cout << "4. 查询成绩" << endl;
        cout << "5. 退出" << endl;
    }

    void run() {
        while (true) {
            showMenu();

            int choice;
            cin >> choice;

            cin.ignore(); // 忽略换行符

            switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                modifyQuestion();
                break;
            case 3:
                startTest();
                break;
            case 4:
                viewScore();
                break;
            case 5:
                cout << "感谢使用课堂测试系统，再见！" << endl;
                return;
            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
            }
        }
    }
};

int main() {
    TestSystem testSystem;
    testSystem.run();

    return 0;
}
