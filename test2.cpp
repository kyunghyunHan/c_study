#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// 정렬 정책의 공통 인터페이스
class SortPolicy {
public:
    // 부모 포인터로 삭제해도 자식 소멸자가 호출되도록 설정
    virtual ~SortPolicy() = default;

    // 순수 가상 함수: 자식 클래스에서 반드시 구현
    virtual void sort(std::vector<int>& numbers) const = 0;
};

// 실제 정렬 알고리즘
class BubbleSort final : public SortPolicy {
public:
    void sort(std::vector<int>& numbers) const override {
        for (std::size_t end = numbers.size(); end > 1; --end) {
            bool swapped = false;

            for (std::size_t i = 1; i < end; ++i) {
                if (numbers[i - 1] > numbers[i]) {
                    const int temp = numbers[i - 1];
                    numbers[i - 1] = numbers[i];
                    numbers[i] = temp;

                    swapped = true;
                }
            }

            // 교환이 없다면 이미 정렬된 상태
            if (!swapped) {
                break;
            }
        }
    }
};

enum class SortType {
    Bubble
};

// 정책 객체를 소유하고 요청한 정책을 제공
class SortFactory {
private:
    // 합성 관계:
    // 팩토리가 사라지면 소유한 정책도 자동으로 삭제됨
    std::vector<std::unique_ptr<SortPolicy>> policies_;

public:
    SortFactory() {
        policies_.push_back(std::make_unique<BubbleSort>());
    }

    SortPolicy& getSortPolicy(SortType type) const {
        switch (type) {
        case SortType::Bubble:
            return *policies_.at(0);
        }

        throw std::invalid_argument("지원하지 않는 정렬 종류");
    }
};

// 정렬 알고리즘의 세부 구현을 몰라도 사용하는 클래스
class User {
private:
    SortFactory& factory_;           // 팩토리는 빌려서 사용
    SortPolicy* policy_ = nullptr;   // 선택한 정책도 빌려서 사용

public:
    explicit User(SortFactory& factory)
        : factory_(factory) {}

    void sortNumbers(std::vector<int>& numbers, SortType type) {
        policy_ = &factory_.getSortPolicy(type);

        // 실제 객체가 BubbleSort이면 BubbleSort::sort() 호출
        policy_->sort(numbers);
    }
};

int main() {
    // User보다 먼저 생성되어 User보다 오래 살아 있음
    SortFactory factory;
    User user(factory);

    std::vector<int> numbers = {5, 2, 9, 1, 3};

    user.sortNumbers(numbers, SortType::Bubble);

    for (int number : numbers) {
        std::cout << number << ' ';
    }
    std::cout << '\n';
}