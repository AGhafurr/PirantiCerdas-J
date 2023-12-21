<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "praktikummodul4";

if (isset($_GET["angka_sumbu"]) && isset($_GET["kemiringan"])) {
    $angka_sumbu = $_GET["angka_sumbu"];
    $kemiringan = $_GET["kemiringan"];

    // Koneksi ke database
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Cek koneksi
    if ($conn->connect_error) {
        die("Koneksi ke database gagal: " . $conn->connect_error);
    }

    // Query untuk memasukkan data ke dalam database
    $sql = "INSERT INTO praktikum4 (angka_sumbu, kemiringan) VALUES ('$angka_sumbu', '$kemiringan')";

    if ($conn->query($sql) === TRUE) {
        echo "Data berhasil disimpan";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    // Tutup koneksi ke database
    $conn->close();
} else {
    echo "Data tidak lengkap";
}
?>
