#include "task.h"
#include "http/htmlpagegetter.h"

Task::Task(QObject *parent) : QObject(parent) {
    id = 0;
}

Task::~Task() {
    if(model != 0) {
        delete model;
    }
    if(processor != 0) {
        delete processor;
    }
}

void Task::setType(int nType) {
    type = nType;
    switch (type) {
    case 1:
        processor = new ProcessorLinks;
        break;
    case 3:
        processor = new ProcessorLists;
        break;
    case 4:
        processor = new ProcessorImages;
        break;
    case 8:
        processor = new ProcessorPrintScreen;
        break;
    case 9:
        processor = new ProcessorInputs;
        break;
    default:
        emit error(QString("Err: Unknown task type."));
    }
}


void Task::process(QString url) {
    emit started();
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    model = processor->process(html, url).get();
    emit finished();
}
