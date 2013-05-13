/*
* FTPPort
* Creates and parses FTP port information
*
* Created in 2012
* Bryan Cairns - bcairns@voidrealms.com
* http://www.voidrealms.com
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FTPPORT_H
#define FTPPORT_H

#include <QObject>
#include <QStringList>
#include <QDebug>

class FTPPort : public QObject
{
    Q_OBJECT
public:
    explicit FTPPort(QObject *parent = 0);
    FTPPort(QString aIPAddress, uint aPort, QObject *parent);
signals:

public slots:

public:

    /*!
    * Gets the IPAddress
    */
    QString IPAddress();

    /*!
    * Sets the IP Address
    * @param IPAddress The IP Address
    */
    void SetIPAddress(QString nIPAddress);

    /*!
    * Gets the Port number
    */
    quint16 Port();

    /*!
    * Sets the Port number
    * @param Port The Port number
    */
    void SetPort(quint16 nPort);

    /*!
    * Gets the string representation
    */
    QString ToString();

    /*!
    * Parses a string and gets the information
    * @param Data The string data
    */
    void FromString(QString Data);

    /*!
    * Clears the information
    */
    void Clear();

private:
    QString mIPAddress;     //! The IP Address
    quint16 mPort;          //! The Port number

};

#endif // FTPPORT_H
