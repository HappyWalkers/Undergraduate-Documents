from workers import app

url='http://www.csu.edu.cn/'

if __name__ == '__main__':
    app.send_task('task.thread_crawling', args=(url,))