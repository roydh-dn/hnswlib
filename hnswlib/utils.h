#pragma once

#include <limits>
#include <random>
#include <vector>

namespace hnswlib {

enum class SpecialValueType {
    NORMAL,        // Regular normalized values (0.0~1.0)
    NOT_A_NUMBER,  // Not a Number (NaN)
    DENORMAL,      // Denormalized small values
    INF            // Infinity
};

struct ValueConfig {
    float ratio;
    SpecialValueType type;
};

class SpecialVectorGenerator {
   public:
    static std::vector<float> generate(size_t vec_dim, size_t size, int seed) {
        std::vector<float> vec_data(vec_dim * size);
        std::mt19937 gen(seed);

        // Define distributions for generating special values
        std::uniform_real_distribution<float> dis_norm(0.0f, 1.0f);
        std::uniform_real_distribution<float> dis_denorm(0.0f, std::numeric_limits<float>::min());
        std::uniform_real_distribution<float> dis_type(0.0f, 1.0f);

        static const ValueConfig value_configs[] = {
            {0.7f, SpecialValueType::NORMAL},        // 70% normal values
            {0.1f, SpecialValueType::NOT_A_NUMBER},  // 10% NaN
            {0.1f, SpecialValueType::DENORMAL},      // 10% denormal values
            {0.1f, SpecialValueType::INF}            // 10% infinity
        };

        for (size_t i = 0; i < vec_dim * size; ++i) {
            float rand_val = dis_type(gen);
            float cumulative_ratio = 0.0f;

            for (const auto& config : value_configs) {
                cumulative_ratio += config.ratio;
                if (rand_val < cumulative_ratio) {
                    vec_data[i] = generateValue(config.type, dis_norm, dis_denorm, gen);
                    break;
                }
            }
        }
        return vec_data;
    }

   private:
    static float generateValue(SpecialValueType type, std::uniform_real_distribution<float>& dis_norm,
                               std::uniform_real_distribution<float>& dis_denorm, std::mt19937& gen) {
        switch (type) {
            case SpecialValueType::NORMAL:
                return dis_norm(gen);
            case SpecialValueType::NOT_A_NUMBER:
                return std::numeric_limits<float>::quiet_NaN();
            case SpecialValueType::DENORMAL:
                return dis_denorm(gen);
            case SpecialValueType::INF:
                return std::numeric_limits<float>::infinity();
            default:
                return 0.0f;
        }
    }
};
}  // namespace hnswlib
