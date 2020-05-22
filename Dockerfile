FROM python:3.6-alpine

WORKDIR /usr/trashly

COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt
COPY . .

ENTRYPOINT ["./entrypoint.sh"]
