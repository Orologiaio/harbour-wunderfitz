/*
    Copyright (C) 2016-18 Sebastian J. Wolf

    This file is part of Wunderfitz.

    Wunderfitz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Wunderfitz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wunderfitz. If not, see <http://www.gnu.org/licenses/>.
*/

#include "cloudapi.h"

CloudApi::CloudApi(QObject *parent) : QObject(parent)
{
    this->networkAccessManager = new QNetworkAccessManager(this);
}

void CloudApi::opticalCharacterRecognition(const QString &imagePath)
{
    qDebug() << "CloudApi::opticalCharacterRecognition" << imagePath;

    QUrl url = QUrl(QString(API_OCR));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    request.setRawHeader(QByteArray("Ocp-Apim-Subscription-Key"), QByteArray(AZURE_COMPUTER_VISION_KEY));
    QUrlQuery urlQuery = QUrlQuery();
    urlQuery.addQueryItem("language", "unk");
    urlQuery.addQueryItem("detectOrientation", "true");
    url.setQuery(urlQuery);

    QFile *file = new QFile(imagePath);
    file->open(QIODevice::ReadOnly);
    QByteArray rawImage = file->readAll();
    file->close();
    file->deleteLater();

    QNetworkReply *reply = networkAccessManager->post(request, rawImage);
    reply->setObjectName(imagePath);

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleOcrUploadError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleOcrUploadFinished()));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(handleOcrUploadProgress(qint64,qint64)));
}

void CloudApi::handleOcrUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "CloudApi::handleOcrUploadProgress" << bytesSent << bytesTotal;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    emit ocrUploadStatus(reply->objectName(), bytesSent, bytesTotal);
}

void CloudApi::handleOcrUploadError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    qWarning() << "CloudApi::handleOcrUploadError:" << (int)error << reply->errorString() << reply->readAll();
    emit ocrUploadError(reply->objectName(), reply->errorString());
}

void CloudApi::handleOcrUploadFinished()
{
    qDebug() << "CloudApi::handleOcrUploadFinished";
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll());
    if (jsonDocument.isObject()) {
        emit ocrUploadSuccessful(reply->objectName(), jsonDocument.object());
    } else {
        emit ocrUploadError(reply->objectName(), "Wunderfitz couldn't understand Azure's response!");
    }
}
