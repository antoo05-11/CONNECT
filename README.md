 HỌ VÀ TÊN: **NGŨ THÀNH AN**
 
 MÃ SINH VIÊN: **21020271**

# CONNECT <img width="38" alt="icon" src="https://user-images.githubusercontent.com/92411733/169693834-3ee68b4a-0535-4ffe-9f58-5fb9d6576c79.png">
## Hướng dẫn cài đặt
1. Các bạn nhấn vào [đây](https://vnueduvn-my.sharepoint.com/:u:/g/personal/21020271_vnu_edu_vn/ER-Gvm7mh7ZPjctkTXBshMQBZ53Ua01NyrmSykK_O3GWzg?e=qNdvTL) và tải về, có thể giải nén hoặc không.
2. Mở file Connect.exe và bắt đầu chơi game.
## Mô tả trò chơi và các ý tưởng chính
- Trò chơi **CONNECT** yêu cầu các bạn sử dụng chuột nối các ô tròn có cùng màu với nhau để lấp đầy bảng. Mỗi round ứng với một lượng thời gian khác nhau, khi thời gian kết thúc mà bảng vẫn chưa được lấp đầy thì thua cuộc.
- **Ý tưởng:** Sử dụng các Vector lưu trữ tọa độ các ô xuất phát, các ô khởi điểm và trạng thái lên xuống trái phải của các đoạn đường đi. Các vector này liên tục được push_back, emplace, clear và erase. Mọi thao tác chuột của người dùng cần được xử lý ở mọi trường hợp, tránh việc truy xuất phần tử nằm ngoài vector do các vector có kích thước thay đổi liên tục.
## Mô tả các chức năng đã cài đặt
- Sau khi game khởi động, ở sảnh chờ, bạn có một MENU các lựa chọn sau:

|Button|Usage|
|-----|-----|
|![8](https://user-images.githubusercontent.com/92411733/169694807-eaa4d7de-64c7-45d9-a652-593d6c05d93e.png)|Nút Start - Bắt đầu chơi game|
|![7](https://user-images.githubusercontent.com/92411733/169694809-ececb9e6-e273-4653-bd76-21ec26c436dd.png)|Hiển thị bảng xếp hạng|
|![6](https://user-images.githubusercontent.com/92411733/169694808-bc935ef6-bcf2-4e79-ade4-6216583062c5.png)|Hiển thị danh sách bản nhạc, cho phép bạn lựa chọn, nghe thử|

- Sau khi bấm nút Start, bạn nhập tên của mình vào và chương trình sẽ lưu trữ thông tin tạm thời. 
- Sau khi nhập tên rồi bấm ENTER, bạn bắt đầu chơi game. Hãy nối những ô tròn cùng màu nhanh nhất có thể để lấp đầy bảng. Chương trình đã thiết lập mọi trường hợp mà bạn thao tác với chuột, chẳng hạn như đường đang đi đâm một đường có sẵn, hay xuất phát tại một điểm trên một đường có sẵn rồi. Các ô gạch chắn đường đi được thiết lập không cho các đường màu của bạn đi qua. Một số ô gạch có thể có cầu, giúp bạn đi 2 đường đè lên nhau tại điểm cầu.
- Trong lúc chơi, bạn có các nút lựa chọn sau:

|Button|Usage|
|-----|-----|
|![5](https://user-images.githubusercontent.com/92411733/169695082-0722123a-4aed-46e5-928a-3b7d5c5533c0.png)|Pause Game|
|![1](https://user-images.githubusercontent.com/92411733/169695085-866a75c3-4955-46a4-b216-de722573dc5a.png)|Return về Round 1|
|![4](https://user-images.githubusercontent.com/92411733/169695086-d8f2b6c6-0eb1-4c02-a6a7-4910cc9912e3.png)|Pause Music|
|![29](https://user-images.githubusercontent.com/92411733/169696223-cc627e75-d461-4c5a-a6e8-067d708fabb3.png)|Resume Game|

- Khi thua ở một round nào đó, nếu round bạn đạt được thuộc top bảng xếp hạng thì sẽ được cập nhật ngay lập tức. Đồng thời, nếu vòng bạn đạt được cao hơn top 1 bảng xếp hạng hiện thời thì game sẽ hiển thị HIGH_SCORE.
### Nhấn vào [đây](https://youtu.be/lT4ph4BD-RI) để xem video demo trò chơi.
### PREVIEW 
<img width="259" alt="Screenshot 2022-05-22 152805" src="https://user-images.githubusercontent.com/92411733/169694749-ddf61523-b28b-4983-ad74-ed74718d6a8f.png"> <img width="266" alt="Screenshot 2022-05-22 152200" src="https://user-images.githubusercontent.com/92411733/169694754-973c67e9-5244-49dc-ae14-2b51b7382346.png"> <img width="265" alt="Screenshot 2022-05-22 152214" src="https://user-images.githubusercontent.com/92411733/169694755-c7161082-7b60-4745-aad1-f4c0a1dbbe94.png"> <img width="260" alt="Screenshot 2022-05-22 152300" src="https://user-images.githubusercontent.com/92411733/169694756-f23ad9c7-be6f-4858-8623-12c6113fe33d.png"> <img width="266" alt="Screenshot 2022-05-22 152121" src="https://user-images.githubusercontent.com/92411733/169694751-b0291cb9-10ff-4990-aa06-a2d734dfaa40.png"> <img width="264" alt="Screenshot 2022-05-22 152140" src="https://user-images.githubusercontent.com/92411733/169694752-f4d730e6-b2de-4ac9-ba2e-c2a49434c2f7.png">

## Các kỹ thuật lập trình được sử dụng trong chương trình
- Pointer.
- Vector.
- Class (Lớp button, lớp Timer, lớp BaseObject, lớp Music,...).
- Kỹ thuật Tile_map (lưu trữ thông tin map dưới dạng .txt).
- Đọc xuất file.
## Kết luận và hướng phát triển
### Thông tin về code và tài nguyên
- Em học SDL2 từ kênh [phát triển phần mềm 123az](https://phattrienphanmem123az.com/) và web [Lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php), em tham khảo lớp BaseObject và lớp Timer.
- Em tự viết toàn bộ code, tự triển khai _logic game_.
- Phần tài nguyên hình ảnh và âm nhạc mặc định em lấy từ game CONNECT thuộc game My Talking Tom trên Android.
### Những điều đã đạt được sau khi code
- Em đã khá thành thạo với thư viện SDL2, với lập trình hướng đối tượng, sử dụng các class.
- Logic game đã xét hết mọi khả năng nhận đầu vào từ người dùng.
- Trò chơi có nhiều tính năng hay như chọn nhạc, xem bảng xếp hạng, hay nhiều nút tính năng như Pause Game, Pause Music, khung chạy thời gian trong lúc chơi ...
### Một số nhược điểm và hướng phát triển
- Các map vẫn còn cố định về màu sắc các ô tròn, em sẽ bổ sung random màu ở mỗi map.
- Mỗi level mới chỉ có một map cố định, em dự định sẽ thêm nhiều map cho một level, sau đó sử dụng random map.
- Vì ban đầu em còn chưa thạo nên phần logic game "HandleEvent" chính em còn sử dụng hàm thường, do đó nhìn code hơi rườm rà, các biến khởi tạo còn khá lộn xộn. Em sẽ thay đổi sang class và tạo lớp GameEngine giúp code gọn hơn.
