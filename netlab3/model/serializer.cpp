#include "serializer.h"

QString Serializer::serialize(std::tr1::shared_ptr<Model> model) {
//    switch(model->getType()) {
//        case TypeQ1:
//            ModelQ1* modelQ1 = dynamic_cast<ModelQ1*>(model.get());
//            if(modelQ1 != NULL) {
//                QString serialized = "";
//                //append fields
//                return serialized;
//            }
//            break;
//        case TypeQ3:
//            ModelQ3* modelQ3 = dynamic_cast<ModelQ3*>(model.get());
//            if(modelQ2 != NULL) {
//                QString serialized = "";
//                //append fields
//                return serialized;
//            }
//            break;
//        case TypeQ4:
//            ModelQ4* modelQ4 = dynamic_cast<ModelQ4*>(model.get());
//            if(modelQ4 != NULL) {
//                QString serialized = "";
//                //append fields
//                return serialized;
//            }
//            break;
//        case TypeQ8:
//            ModelQ8* modelQ8 = dynamic_cast<ModelQ8*>(model.get());
//            if(modelQ8 != NULL) {
//                QString serialized = "";
//                //append fields
//                return serialized;
//            }
//            break;
//        case TypeQ9:
//            ModelQ9* modelQ9 = dynamic_cast<ModelQ9*>(model.get());
//            if(modelQ9 != NULL) {
//                QString serialized = "";
//                //append fields
//                return serialized;
//            }
//            break;
//    }
    return QString::number(model->getType());
}

std::tr1::shared_ptr<Model> deserialize(Type type, const QString& data) {
//    switch(type) {
//        case TypeQ1:
//            std::tr1::shared_ptr<Model> modelQ1(new ModelQ1());
//            //initialize fields
//            return modelQ1;
//        case TypeQ3:
//            std::tr1::shared_ptr<Model> modelQ3(new ModelQ3());
//            //initialize fields
//            return modelQ3;
//        case TypeQ4:
//            std::tr1::shared_ptr<Model> modelQ4(new ModelQ4());
//            //initialize fields
//            return modelQ4;
//        case TypeQ8:
//            std::tr1::shared_ptr<Model> modelQ8(new ModelQ8());
//            //initialize fields
//            return modelQ8;
//            break;
//        case TypeQ9:
//            std::tr1::shared_ptr<Model> modelQ9(new ModelQ9());
//            //initialize fields
//            return modelQ9;
//            break;
//    }
    //will it works? :D
    std::tr1::shared_ptr<Model> nullModel((Model*)NULL);
    return nullModel;
}
