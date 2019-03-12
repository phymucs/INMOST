//
// Created by bvdmitri on 10.02.19.
//

#include "ttsp_alternating.h"

namespace TTSP {

    AlternatingParameterHandler::AlternatingParameterHandler(const OptimizationParameter &parameter) :
            parameter(parameter), direction(AlternatingDirection::RIGHT), current_index(0) {}

    AlternatingParameterHandler::AlternatingParameterHandler(const AlternatingParameterHandler &other) :
            parameter(other.parameter), direction(other.direction), current_index(other.current_index) {}

    const OptimizationParameter &AlternatingParameterHandler::GetParameter() const {
        return parameter;
    }

    std::size_t AlternatingParameterHandler::GetDirection() const {
        return direction;
    }

    std::size_t AlternatingParameterHandler::GetCurrentIndex() const {
        return current_index;
    }

    std::size_t AlternatingParameterHandler::NextIndex() const {
        std::size_t count = parameter.GetValues().size() - 1;
        std::size_t index = current_index;

        switch_direction:
        switch (direction) {
            case RIGHT:
                if (index == count) {
                    direction = LEFT;
                    goto switch_direction;
                } else {
                    index += 1;
                }
                break;
            case STAY1:
                break;
            case LEFT:
                if (index == 0) {
                    direction = RIGHT;
                    goto switch_direction;
                } else {
                    index -= 1;
                }
                break;
            case STAY2:
                break;
            default:
                break;
        }
        return index;
    }

    void AlternatingParameterHandler::NextDirection() {
        direction = (direction + 1) % 4;
    }

    void AlternatingParameterHandler::UpdateIndex(std::size_t index) {
        current_index = index;
    }

    AlternatingOptimizer::AlternatingOptimizer(const OptimizationParameters &space, const OptimizerProperties &properties, std::size_t buffer_capacity) :
            OptimizerInterface(space, properties, buffer_capacity), current_handler_index(0) {
        const OptimizationParameterEntries &parameters = space.GetParameterEntries();
        handlers.reserve(parameters.size());
        std::for_each(parameters.begin(), parameters.end(), [this](const OptimizationParametersEntry &entry) {
            handlers.emplace_back(AlternatingParameterHandler(entry.first));
        });
    }

    OptimizationParametersSuggestion AlternatingOptimizer::Suggest(const std::function<OptimizationFunctionInvokeResult(const OptimizationParameterPoints &,
                                                                                                                        const OptimizationParameterPoints &,
                                                                                                                        void *)> &invoke, void *data) const {

        OptimizationParameterPoints points(parameters.GetParameterEntries().size());

        int i = 0;
        std::transform(handlers.begin(), handlers.end(), points.begin(), [this, &i](const AlternatingParameterHandler &h) {
            return std::make_pair(
                    h.GetParameter().GetName(),
                    h.GetParameter().GetValues().at(i++ == current_handler_index ? h.NextIndex() : h.GetCurrentIndex())
            );
        });

        return OptimizationParametersSuggestion(handlers.at(current_handler_index).GetParameter(), parameters.GetPoints(), parameters.GetMetrics(), points);
    }

    void AlternatingOptimizer::UpdateSpaceWithLatestResults() {
        AlternatingParameterHandler       &current = handlers.at(current_handler_index);
        const OptimizationParameterResult &last    = results.at(0);

        if (last.IsGood() && (last.GetMetricsBefore() < 0.0 || last.GetMetricsAfter() < last.GetMetricsBefore())) {
            current.UpdateIndex(current.NextIndex());
            parameters.Update(current_handler_index, parameters.GetParameter(current_handler_index).GetValues().at(current.GetCurrentIndex()), last.GetMetricsAfter());
        } else {
            current.NextDirection();
        }

        current_handler_index = (current_handler_index + 1) % (handlers.size());
    }

    AlternatingOptimizer::~AlternatingOptimizer() {}


}
