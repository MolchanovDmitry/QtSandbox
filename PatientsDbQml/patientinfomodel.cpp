#include "patientinfomodel.h"

PatientInfoModel::PatientInfoModel(QObject *parent)
    : QObject{parent}
{

}

const QString &PatientInfoModel::getText() const
{
    return text;
}
