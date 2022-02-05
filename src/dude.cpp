#include "./Presenter/Presenter.h"
#include "./View/View.h"
#include "./Rules/Rule_1.h"

int main()
{
    View* view = View::get_instance();
    Presenter<Rule_1<10>, Rule_2<2>, Rule_3<2>> presenter(view);

    presenter.start();
}
