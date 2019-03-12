//
// Created by bvdmitri on 31.01.19.
//

#ifndef INMOST_TTSP_BRUTEFORCE_H
#define INMOST_TTSP_BRUTEFORCE_H

#include <Source/Solver/ttsp/ttsp.h>

namespace TTSP {

    class BruteforceOptimizer : public OptimizerInterface {
    public:
        BruteforceOptimizer(const OptimizationParameters &space, const OptimizerProperties &properties, std::size_t buffer_capacity);

        OptimizationParametersSuggestion Suggest(const std::function<OptimizationFunctionInvokeResult(const OptimizationParameterPoints &,
                                                                                                      const OptimizationParameterPoints &,
                                                                                                      void *)> &invoke, void *data) const override;

        virtual ~BruteforceOptimizer();
    };

}


#endif //INMOST_TTSP_BRUTEFORCE_H
