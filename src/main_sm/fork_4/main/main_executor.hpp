#ifndef MAIN_EXECUTOR_HPP_fork_4
#define MAIN_EXECUTOR_HPP_fork_4

#include <string>
#include <nlohmann/json.hpp>
#include <pthread.h>
#include <semaphore.h>
#include "config.hpp"
#include "main_sm/fork_4/main/rom.hpp"
#include "main_sm/fork_4/main/context.hpp"
#include "main_sm/fork_4/pols_generated/commit_pols.hpp"
#include "main_sm/fork_4/main/main_exec_required.hpp"
#include "scalar.hpp"
#include "hashdb_factory.hpp"
#include "poseidon_goldilocks.hpp"
#include "counters.hpp"
#include "goldilocks_base_field.hpp"
#include "prover_request.hpp"

using namespace std;
using json = nlohmann::json;

namespace fork_4
{

class MainExecutor {
public:

    // Finite field data
    Goldilocks &fr; // Finite field reference

    // RawFec instance
    RawFec fec;

    // RawFnec instance
    RawFnec fnec;

    // Number of evaluations, i.e. polynomials degree
    const uint64_t N;

    // Number of evaluations when counters are not used
    const uint64_t N_NoCounters;

    // Poseidon instance
    PoseidonGoldilocks &poseidon;

    // ROM JSON file data:
    Rom rom;

    // Database server configuration, if any
    const Config &config;

    // ROM labels
    uint64_t finalizeExecutionLabel;
    uint64_t checkAndSaveFromLabel;
    uint64_t ecrecoverStoreArgsLabel;

    // Constructor
    MainExecutor(Goldilocks &fr, PoseidonGoldilocks &poseidon, const Config &config);

    // Destructor
    ~MainExecutor();

    void execute (ProverRequest &proverRequest, MainCommitPols &cmPols, MainExecRequired &required);

    // Initial and final evaluations/state management
    void initState(Context &ctx);
    void checkFinalState(Context &ctx);
    void assertOutputs(Context &ctx);
    void logError(Context &ctx, const string &message = "");
};

} // namespace

#endif