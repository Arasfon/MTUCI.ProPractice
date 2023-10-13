#include "pch.h"
#include "ExamController.h"
#if __has_include("ExamController.g.cpp")
#include "ExamController.g.cpp"
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::ProPractice::implementation
{
    ExamController::ExamController()
    {
        _questions = single_threaded_vector<ExamQuestion>();
    }

    int32_t ExamController::CurrentQuestion()
    {
        return _currentQuestion;
    }

    void ExamController::CurrentQuestion(int32_t const& value)
    {
        _currentQuestion = value;
    }

    IVector<ExamQuestion> ExamController::Questions()
    {
        return _questions;
    }

    event_token ExamController::OnControlAction(EventHandler<ExamControlAction> const& handler)
    {
        return _onControlActionEvent.add(handler);
    }

    void ExamController::OnControlAction(event_token const& token) noexcept
    {
        _onControlActionEvent.remove(token);
    }

    void ExamController::CallControl(const ExamControlAction action)
    {
        _onControlActionEvent(*this, action);
    }
}