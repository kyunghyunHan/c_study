#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t (*fan_power)(float temperature);
} CoolingStrategy;

uint8_t on_off_power(float temperature)
{
    return temperature >= 40.0f ? 100 : 0;
}

uint8_t proportional_power(float temperature)
{
    float power = (temperature - 40.0f) * 10.0f;

    if (!(power > 0.0f))
    {
        return 0;
    }

    if (power >= 100.0f)
    {
        return 100;
    }

    return (uint8_t)power;
}

// 전달받은 전략의 함수를 호출
void run(const CoolingStrategy *strategy, float temperature)
{
    printf("팬 출력: %u%%\n",
           (unsigned int)strategy->fan_power(temperature));
}

int main(void)
{
    const CoolingStrategy on_off = {
        .fan_power = on_off_power};

    const CoolingStrategy proportional = {
        .fan_power = proportional_power};

    run(&on_off, 43.0f);       // 팬 출력: 100%
    run(&proportional, 43.0f); // 팬 출력: 30%

    return 0;
}

typedef struct Sort
{
    int *(*sort)(int *arr);

} Sort;