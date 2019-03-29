//
// Created by bvdmitri on 31.01.19.
//

#ifndef INMOST_TTSP_DEFAULT_H
#define INMOST_TTSP_DEFAULT_H

#include <inmost_ttsp.h>

namespace TTSP {

    class NoopOptimizer : public OptimizerInterface {
    protected:
        SuggestionChangedParameters AlgorithmMakeSuggestion(const std::function<OptimizationFunctionInvokeResult(const OptimizationParameterPoints &,
                                                                                                               const OptimizationParameterPoints &,
                                                                                                               void *)> &invoke, void *data) const override;

    public:
        NoopOptimizer(const std::string &name, const OptimizationParameters &space, const OptimizerProperties &properties, std::size_t buffer_capacity);

        virtual ~NoopOptimizer();
    };

}

#endif //INMOST_TTSP_DEFAULT_H